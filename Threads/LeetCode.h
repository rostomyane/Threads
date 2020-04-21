#pragma once

#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <string>
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
		unordered_set<string> result;
		int left_removed = 0;
		int right_removed = 0;
		for (auto c : s) {
			if (c == '(') {
				++left_removed;
			}
			if (c == ')') {
				if (left_removed != 0) {
					--left_removed;
				}
				else {
					++right_removed;
				}
			}
		}
		helper(s, 0, left_removed, right_removed, 0, "", result);
		return vector<string>(result.begin(), result.end());
	}
private:
	void helper(string s, int index, int left_removed, int right_removed, int pair, string path, unordered_set<string>& result) {
		if (index == s.size()) {
			if (left_removed == 0 && right_removed == 0 && pair == 0) {
				result.insert(path);
			}
			return;
		}
		if (s[index] != '(' && s[index] != ')') {
			helper(s, index + 1, left_removed, right_removed, pair, path + s[index], result);
		}
		else {
			if (s[index] == '(') {
				if (left_removed > 0) {
					helper(s, index + 1, left_removed - 1, right_removed, pair, path, result);
				}
				helper(s, index + 1, left_removed, right_removed, pair + 1, path + s[index], result);
			}
			if (s[index] == ')') {
				if (right_removed > 0) {
					helper(s, index + 1, left_removed, right_removed - 1, pair, path, result);
				}
				if (pair > 0) {
					helper(s, index + 1, left_removed, right_removed, pair - 1, path + s[index], result);
				}
			}
		}
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