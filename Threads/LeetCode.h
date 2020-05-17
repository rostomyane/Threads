#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <sstream>
using namespace std;

struct Node {
public:
	int val;
	Node* left;
	Node* right;
};

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {}
};


/* M
Given a binary tree, return the vertical order traversal of its nodes values.
*/
class VerticalTraversal {
	int left, right;
public:
	vector<vector<int>> verticalTraversal(TreeNode* root) {
		unordered_map<int, set < pair<int, int>>> H;
		traverse(root, H, 0, 0);
		vector<vector<int>> res;
		for (int i = left; i <= right; ++i)
		{
			auto v = H[i];
			vector<int> curr;
			for (auto it : v) { curr.push_back(it.second); }
			res.push_back(curr);
		}
		return res;
	}

	template<class T>
	void traverse(TreeNode* root, T& H, int level, int h)
	{
		if (root)
		{
			left = min(left, level);
			right = max(right, level);
			H[level].insert({ h,root->val });
			traverse(root->left, H, level - 1, h + 1);
			traverse(root->right, H, level + 1, h + 1);
		}
	}
};


/* H
Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
*/
class MergeKLists {
public:
	ListNode* mergeKLists(vector<ListNode*> lists) {
		if (lists.empty()) { return NULL; }
		if (lists.size() == 1) { return lists[0]; }
		if (lists.size() == 2) { return mergeTwoLists(lists[0], lists[1]); }

		int mid = lists.size() / 2;
		ListNode* left = mergeKLists({ lists.begin(),lists.begin() + mid });
		ListNode* right = mergeKLists({ lists.begin() + mid,lists.end() });
		return mergeTwoLists(left, right);

	}

	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		if (!l1) { return l2; }
		if (!l2) { return l1; }
		if (l1->val <= l2->val)
		{
			l1->next = mergeTwoLists(l1->next, l2); return l1;
		}
		else
		{
			l2->next = mergeTwoLists(l1, l2->next); return l2;
		}
	}
};


/* H
Given a non-empty binary tree, find the maximum path sum.
*/
class MaxPathSum {
public:
	int dfs(TreeNode* root, int& path)
	{
		if (root)
		{
			int left = max(0, dfs(root->left, path));
			int right = max(0, dfs(root->right, path));
			path = max(path, left + right + root->val);
			return max(left, right) + root->val;
		}
		return 0;
	}
	int maxPathSum(TreeNode* root) {
		int path = INT_MIN;
		dfs(root, path);
		return path;
	}
};


/*M
Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1 ... n.
Hint: for N there are f(N) such trees, where f(N) denotes the N-th Catalan number
*/
class GenerateAllBST {
public:
	vector<TreeNode*> createTree(int start, int end) {
		if (end < start) { return { nullptr }; };

		vector<TreeNode*> ans;
		for (int i = start; i <= end; i++) {
			vector<TreeNode*> left_subtree, right_subtree;
			left_subtree = createTree(start, i - 1);
			right_subtree = createTree(i + 1, end);

			for (int j = 0; j < left_subtree.size(); j++) {
				for (int k = 0; k < right_subtree.size(); k++) {
					TreeNode* root = new TreeNode(i);
					root->left = left_subtree[j];
					root->right = right_subtree[k];
					ans.emplace_back(root);
				}
			}

		}
		return ans;
	}

	vector<TreeNode*> generateTrees(int n) {
		if (n <= 0)
			return {};
		return createTree(1, n);
	}
};


/*E
Given an array of integers nums, write a method that returns the "pivot" index of this array.
We define the pivot index as the index where the sum of the numbers to the left of the index is equal to the sum of the numbers to the right of the index.
If no such index exists, we should return -1. If there are multiple pivot indexes, you should return the left-most pivot index.
*/
class PivotIndex {
public:
	int pivotIndex(vector<int>& nums) {
		int total = 0;
		for (int num : nums) total += num;
		int sum = 0;
		for (int i = 0; i < nums.size(); sum += nums[i++])
			if (sum * 2 == total - nums[i])
				return i;

		return -1;
	}
};


/*H
Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).
If there is no such window in S that covers all characters in T, return the empty string "".
If there is such window, you are guaranteed that there will always be only one unique minimum window in S.
*/
class MinWindow {
public:
	string minWindow(string s, string t) {
		unordered_map<char, int> letters;
		for (auto c : t) letters[c]++;
		int count = 0;
		int low = 0, min_length = INT_MAX, min_start = 0;
		for (int high = 0; high < s.length(); high++) {
			if (letters[s[high]] > 0) { count++; }
			letters[s[high]]--;
			if (count == t.length()) {
				while (low < high && letters[s[low]] < 0) { letters[s[low]]++, low++; }
				if (min_length > high - low) { min_length = high - (min_start = low) + 1; }
				letters[s[low++]]++;
				count--;
			}
		}
		return min_length == INT_MAX ? "" : s.substr(min_start, min_length);
	}
};


/*H
Given a string, find the length of the longest substring T that contains at most k distinct characters.
*/
class MaxSubarrayKDistinct {
public:
	int lengthOfLongestSubstringKDistinct(string s, int k) {
		vector<int> ctr(256);
		int left = -1, distinct = 0, maxlen = 0;
		for (int right = 0; right < s.size(); ++right) {
			distinct += ctr[s[right]]++ == 0;
			while (distinct > k)
				distinct -= --ctr[s[++left]] == 0;
			maxlen = max(maxlen, right - left);
		}
		return maxlen;
	}
};


/*H
Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.
Note: The input string may contain letters other than the parentheses ( and ).
*/
class RemoveInvalidParentheses {
public:
	vector<string> removeInvalidParentheses(string s) {
		vector<string> output;
		removeHelper(s, output, 0, 0, '(', ')');
		return output;
	}

	void removeHelper(string s, vector<string>& output, int iStart, int jStart, char openParen, char closedParen) {
		int numOpenParen = 0, numClosedParen = 0;
		for (int i = iStart; i < s.length(); i++) {
			if (s[i] == openParen) numOpenParen++;
			if (s[i] == closedParen) numClosedParen++;
			if (numClosedParen > numOpenParen) { // We have an extra closed paren we need to remove
				for (int j = jStart; j <= i; j++) // Try removing one at each position, skipping duplicates
					if (s[j] == closedParen && (j == jStart || s[j - 1] != closedParen))
						// Recursion: iStart = i since we now have valid # closed parenthesis thru i. jStart = j prevents duplicates
						removeHelper(s.substr(0, j) + s.substr(j + 1, s.length()), output, i, j, openParen, closedParen);
				return; // Stop here. The recursive calls handle the rest of the string.
			}
		}
		// No invalid closed parenthesis detected. Now check opposite direction, or reverse back to original direction.
		string reversed = s;
		reverse(reversed.begin(), reversed.end());
		if (openParen == '(')
			removeHelper(reversed, output, 0, 0, ')', '(');
		else
			output.push_back(reversed);
	}
};


/*H
Integer to English Words
*/
class IntToString {
public:
	vector<string> digits = { "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven",
	  "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen",
	  "Sixteen", "Seventeen", "Eighteen", "Nineteen" };
	vector<string> tens = { "","Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };

	string intToStr(int n) {
		if (n >= 1000000000) {
			return intToStr(n / 1000000000) + " Billion" + intToStr(n % 1000000000);
		}
		else if (n >= 1000000) {
			return intToStr(n / 1000000) + " Million" + intToStr(n % 1000000);
		}
		else if (n >= 1000) {
			return intToStr(n / 1000) + " Thousand" + intToStr(n % 1000);
		}
		else if (n >= 100) {
			return intToStr(n / 100) + " Hundred" + intToStr(n % 100);
		}
		else if (n >= 20) {
			return  " " + tens[n / 10] + intToStr(n % 10);
		}
		else if (n >= 1) {
			return " " + digits[n];
		}
		else {
			return "";
		}
	}

	string numberToWords(int num) {
		if (num == 0) {
			return "Zero";
		}
		else {
			string ret = intToStr(num);
			return ret.substr(1, ret.length() - 1);
		}
	}
};


/*H
Given a file and assume that you can only read the file using a given method read4,
implement a method read to read n characters. Your method read may be called multiple times.
The API read4 reads 4 consecutive characters from the file, then writes those characters into the buffer array buf.
The return value is the number of actual characters read.
*/
class Read4n {
	int read4(char* buf) { return 0; }
public:
	int read(char* buf, int n) {
		int i = 0;
		while (i < n && (i4 < n4 || (i4 = 0) < (n4 = read4(buf4))))
			buf[i++] = buf4[i4++];
		return i;
	}
	char buf4[4];
	int i4 = 0, n4 = 0;
};


/*H
Given a string that contains only digits 0-9 and a target value, return all possibilities to add
binary operators (not unary) +, -, or *between the digits so they evaluate to the target value.
*/
class AddOperations {
public:
	vector<string> addOperators(string num, int target) {
		vector<string> res;
		dfs(num, 0, target, "", 0, 0, res);
		return res;
	}

	void dfs(string& num, int start, int target, string path, long prev, long cur, vector<string>& res) {
		if (start == num.size() && prev + cur == target) res.push_back(path);

		for (int i = 1; start + i <= num.size(); i++) {
			string s = num.substr(start, i);
			long n = stoll(s);
			if (to_string(n).size() != s.size()) return;
			if (!start) dfs(num, i, target, s, 0, n, res);
			else {
				dfs(num, start + i, target, path + "+" + s, prev + cur, n, res);
				dfs(num, start + i, target, path + "-" + s, prev + cur, -n, res);
				dfs(num, start + i, target, path + "*" + s, prev, cur * n, res);
			}
		}
	}
};


/*M
Convert BST to doble linked list
*/
class TreeToDLL {
public:
	Node* treeToDoublyList(Node* root)
	{
		if (!root) return nullptr;
		Node* head = nullptr;
		Node* prev = nullptr;
		inOrder(root, prev, head);
		prev->right = head;
		head->left = prev;
		return head;
	}

protected:
	void inOrder(Node* node, Node*& prev, Node*& head)
	{
		if (node->left) { inOrder(node->left, prev, head); }
		if (!prev) { head = node; }
		else
		{
			prev->right = node;
			node->left = prev;
		}
		prev = node;
		if (node->right) { inOrder(node->right, prev, head); }
	}
};


/*M
*/
class CPUIntervals {
public:
	int leastInterval(vector<char>& tasks, int n) {
		unordered_map<char, int>mp;
		int count = 0;
		for (auto e : tasks)
		{
			mp[e]++;
			count = max(count, mp[e]);
		}

		int ans = (count - 1) * (n + 1);
		for (auto e : mp) if (e.second == count) ans++;
		return max((int)tasks.size(), ans);
	}
};



/*M
Given a binary tree, flatten it to a linked list in-place.
*/
class FlattenTree {
public:
	void flatten(TreeNode* root) {
		while (root) {
			if (root->left && root->right) {
				TreeNode* t = root->left;
				while (t->right)
					t = t->right;
				t->right = root->right;
			}

			if (root->left)
				root->right = root->left;
			root->left = NULL;
			root = root->right;
		}
	}
};


/*M
Find the kth largest element in an unsorted array.
Note that it is the kth largest element in the sorted order, not the kth distinct element.
*/
class LongestIncreasinPath {
public:
	int dx[4] = { 0, -1, 1, 0 };
	int dy[4] = { 1, 0, 0, -1 };

	vector<vector<int>> dp;

	int dfs(vector<vector<int>>& grid, int i, int j, int prev) {
		if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size()) return 0;
		if (grid[i][j] <= prev) return 0;
		if (dp[i][j] != -1) return dp[i][j];
		int ans = 0;
		for (int k = 0; k < 4; k++) {
			int I = i + dx[k];
			int J = j + dy[k];
			ans = max(ans, 1 + dfs(grid, I, J, grid[i][j]));
		}
		return dp[i][j] = ans;
	}

	int longestIncreasingPath(vector<vector<int>>& matrix) {
		dp = vector<vector<int>>(1000, vector<int>(1000, -1));
		if (!matrix.size()) return 0;
		int ans = 1;
		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[0].size(); j++) {
				ans = max(ans, dfs(matrix, i, j, INT_MIN));
			}
		}
		return ans;
	}
};

/*H
Kth largest element in the array
*/
class KthLargestElement {
public:
	int findKthLargest(vector<int>& nums, int k) {
		int left = 0, right = nums.size() - 1, kth;
		while (true) {
			int idx = partition(nums, left, right);
			if (idx == k - 1) {
				kth = nums[idx];
				break;
			}
			if (idx < k - 1) {
				left = idx + 1;
			}
			else {
				right = idx - 1;
			}
		}
		return kth;
	}
private:
	int partition(vector<int>& nums, int left, int right) {
		int pivot = nums[left], l = left + 1, r = right;
		while (l <= r) {
			if (nums[l] < pivot && nums[r] > pivot) {
				swap(nums[l++], nums[r--]);
			}
			if (nums[l] >= pivot) {
				l++;
			}
			if (nums[r] <= pivot) {
				r--;
			}
		}
		swap(nums[left], nums[r]);
		return r;
	}
};


/*H
Find kth digit int the 123...sequence
*/
class FindKthDigit
{
public:
	int findNthDigit(int n)
	{
		// step 1. calculate how many digits the number has.
		long base = 9, digits = 1;
		while (n - base * digits > 0)
		{
			n -= base * digits;
			base *= 10;
			digits++;
		}

		// step 2. calculate what the number is.
		int index = n % digits;
		if (index == 0)
			index = digits;
		long num = 1;
		for (int i = 1; i < digits; i++)
			num *= 10;
		num += (index == digits) ? n / digits - 1 : n / digits;;

		// step 3. find out which digit in the number is we wanted.
		for (int i = index; i < digits; i++)
			num /= 10;
		return num % 10;
	}
};


/*E
Given a binary tree, you need to compute the length of the diameter of the tree.
The diameter of a binary tree is the length of the longest path between any two nodes in a tree.
This path may or may not pass through the root
*/
class DiameterOfBST {
public:
	int diameterOfBinaryTree(TreeNode* root) {
		int diameter = 0;
		height(root, diameter);
		return diameter;
	}
private:
	int height(TreeNode* node, int& diameter) {
		if (!node) {
			return 0;
		}
		int lh = height(node->left, diameter);
		int rh = height(node->right, diameter);
		diameter = max(diameter, lh + rh);
		return 1 + max(lh, rh);
	}
};


/*M
3sum, find all unique triplets whos sum is 0 
*/
class ThreeSum {
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		int n = nums.size();
		if (n < 3) { return {  }; }
		sort(nums.begin(), nums.end());
		std::vector<std::vector<int>> result;
		for (int i = 0; i < n; ++i)
		{
			int target = -nums[i];
			if (target >= 0)
			{
				int l = i + 1;
				int r = n - 1;
				while (l < r)
				{
					if (nums[l] + nums[r] == target)
					{
						result.push_back({ nums[i], nums[l], nums[r], });
						l++; r--;
						while (l < r && nums[l] == nums[l - 1]) { l++; }
						while (l < r && nums[r] == nums[r + 1]) { r--; }
					}
					else if (nums[l] + nums[r] > target)
					{
						r--;
					}
					else
					{
						l++;
					}

				}

			}
			while (i < n - 1 && nums[i] == nums[i + 1]) { i++; }

		}
		return result;
	}
};


/*M
Copy single linke list with randon link
*/
class CopyRandomList {
	struct Node {
	public:
		int val;
		Node* next;
		Node* random;
		Node(int val) {

		}
	};
public:
	Node* copyRandomList(Node* head) {
		Node* newHead, * l1, * l2;
		if (head == NULL) return NULL;
		for (l1 = head; l1 != NULL; l1 = l1->next->next) {
			l2 = new Node(l1->val);
			l2->next = l1->next;
			l1->next = l2;
		}

		newHead = head->next;
		for (l1 = head; l1 != NULL; l1 = l1->next->next) {
			if (l1->random != NULL) l1->next->random = l1->random->next;
		}

		for (l1 = head; l1 != NULL; l1 = l1->next) {
			l2 = l1->next;
			l1->next = l2->next;
			if (l2->next != NULL) l2->next = l2->next->next;
		}

		return newHead;
	}
};


/*H
RegexMath
*/
class Match {
public:
	bool isMatch(string s, string p) {
		int m = s.size(), n = p.size();
		vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
		dp[0][0] = true;
		for (int i = 0; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				if (p[j - 1] == '*') {
					dp[i][j] = dp[i][j - 2] || (i && dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'));
				}
				else {
					dp[i][j] = i && dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
				}
			}
		}
		return dp[m][n];
	}
};


/*H
Robot clean room
*/
class CleanRoom {
	struct Robot {
		void turnRight(){}
		void clean() {}
		bool move(){}
	};
public:
	unordered_map<int, unordered_map<int, int>> data;
	int x = 0;
	int y = 0;
	int dx[4] = { 1, 0, -1, 0 };
	int dy[4] = { 0, 1, 0, -1 };
	int dir = 0;
	void cleanRoom(Robot& robot) {
		if (data[x][y] == 1) {
			return;
		}
		data[x][y] = 1;
		robot.clean();
		for (int i = 0; i < 4; i++) {
			if (robot.move()) {
				x += dx[dir];
				y += dy[dir];
				cleanRoom(robot);
				robot.turnRight();
				robot.turnRight();
				robot.move();
				robot.turnRight();
				robot.turnRight();
				x -= dx[dir];
				y -= dy[dir];
			}
			robot.turnRight();
			dir = (dir + 1) % 4;
		}
	}
};


/*
Is a valid number? ex 2e10
*/
class IsNumber {
private:
	bool isSpace(char c) { return c == ' '; }
	bool isSgn(char c) { return c == '+' || c == '-'; }
	bool isDot(char c) { return c == '.'; }
	bool isNum(char c) { return c <= '9' && c >= '0'; }
	bool isE(char c) { return c == 'e' || c == 'E'; }

public:
	bool isNumber(string s) {
		int pos = 0;
		bool haveNum = false;

		// Check all the prefix spaces
		while (pos < s.size() && isSpace(s[pos])) pos++;

		// Check the next char if it's a +/- signal
		if (pos < s.size() && isSgn(s[pos])) pos++;

		// Check the numbers before a dot '.'
		while (pos < s.size() && isNum(s[pos])) { haveNum = true; pos++; }

		// Check the dot '.'
		if (pos < s.size() && isDot(s[pos])) pos++;

		// Check the numbers after a dot '.'
		while (pos < s.size() && isNum(s[pos])) { haveNum = true; pos++; }

		// Check the 'e' / 'E'
		if (haveNum && pos < s.size() && isE(s[pos])) {
			haveNum = false; pos++;
			if (pos < s.size() && isSgn(s[pos])) pos++;
		}

		// Check the numbers after 'e' / 'E'
		while (pos < s.size() && isNum(s[pos])) { haveNum = true; pos++; }

		// Check all the remaining spaces
		while (pos < s.size() && isSpace(s[pos])) pos++;

		// Everything is done, if the string not empty, return false.
		return (pos == s.size() && haveNum);
	}
};

class CloneGraph {
	class Node {
	public:
		int val;
		vector<Node*> neighbors;

		Node() {
			val = 0;
			neighbors = vector<Node*>();
		}

		Node(int _val) {
			val = _val;
			neighbors = vector<Node*>();
		}

		Node(int _val, vector<Node*> _neighbors) {
			val = _val;
			neighbors = _neighbors;
		}
	};
public:
	Node* cloneGraph(Node* node) {
		if (!node) {
			return NULL;
		}
		if (copies.find(node) == copies.end()) {
			copies[node] = new Node(node->val, {});
			for (Node* neighbor : node->neighbors) {
				copies[node]->neighbors.push_back(cloneGraph(neighbor));
			}
		}
		return copies[node];
	}
private:
	unordered_map<Node*, Node*> copies;
};


/*M
lenght of longest substring with all distinct chars
*/
class AllDistinctChars {
public:
	int lengthOfLongestSubstring(string s) {
		vector<int> dict(256, -1);
		int maxLen = 0, start = -1;
		for (int i = 0; i != s.length(); i++) {
			if (dict[s[i]] > start)
				start = dict[s[i]];
			dict[s[i]] = i;
			maxLen = max(maxLen, i - start);
		}
		return maxLen;
	}
};


/*M
Multiply 2 strings
*/
class MultiplyString {
public:
	string multiply(string num1, string num2) {
		string sum(num1.size() + num2.size(), '0');

		for (int i = num1.size() - 1; 0 <= i; --i) {
			int carry = 0;
			for (int j = num2.size() - 1; 0 <= j; --j) {
				int tmp = (sum[i + j + 1] - '0') + (num1[i] - '0') * (num2[j] - '0') + carry;
				sum[i + j + 1] = tmp % 10 + '0';
				carry = tmp / 10;
			}
			sum[i] += carry;
		}

		size_t startpos = sum.find_first_not_of("0");
		if (string::npos != startpos) {
			return sum.substr(startpos);
		}
		return "0";
	}
};


/*H
Allien dictionary
*/
class AllienOrder {
	struct Node {
		int previous_chars = 0;  // number of characters that comes before
		vector<char> next_chars{};  // list of characters that come after
	};
public:
	string alienOrder(const vector<string>& words) {
		std::unordered_map<char, Node*> graph;
		for (auto word : words) {
			for (auto c : word) {
				if (!graph.count(c)) {
					graph[c] = new Node();
				}
			}
		}

		for (int i = 0; i < words.size() - 1; ++i) {
			auto s1 = words[i];
			auto s2 = words[i + 1];
			int index = 0;
			int n = min(s1.size(), s2.size());
			while (index < n && s1[index] == s2[index]) { index++; }

			if (index == n) {
				if (s2.size() < s1.size()) { return ""; }
			}

			if (index < n)
			{
				graph[s1[index]]->next_chars.emplace_back(s2[index]);
				graph[s2[index]]->previous_chars++;
			}
		}

		stack<char> process;
		for (auto it : graph) {
			if (it.second->previous_chars == 0) {
				process.push(it.first);
			}
		}

		string order;
		while (!process.empty()) {
			order += process.top();
			process.pop();
			for (auto c : graph[order.back()]->next_chars) {
				graph[c]->previous_chars--;
				if (graph[c]->previous_chars == 0) {
					process.push(c);
				}
			}
		}

		if (order.size() != graph.size()) { return ""; }
		return order;
	}
};

/*
All permutations of array
*/
class Permutations {
public:
	void backtrack(std::vector<std::vector<int>>& res, std::vector<int>& nums, int pos, int n)
	{
		if (pos == n) { res.push_back(nums); }
		for (int i = pos; i < n; ++i)
		{
			swap(nums[pos], nums[i]);
			backtrack(res, nums, pos + 1, n);
			swap(nums[pos], nums[i]);
		}
	}

	vector<vector<int>> permute(vector<int>& nums) {
		std::vector < std::vector<int> > S;
		backtrack(S, nums, 0, nums.size());
		return S;
	}
};

/*
Simplify Unix path
*/
class Simplify {
	string simplifyPath(string path) {
		string res, tmp;
		vector<string> stk;
		stringstream ss(path);
		while (getline(ss, tmp, '/')) {
			if (tmp == "" or tmp == ".") continue;
			if (tmp == ".." and !stk.empty()) stk.pop_back();
			else if (tmp != "..") stk.push_back(tmp);
		}
		for (auto str : stk) res += "/" + str;
		return res.empty() ? "/" : res;
	}
};