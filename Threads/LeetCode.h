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
class Solution {
public:
	string minWindow(string s, string t) {
		unordered_map<char, int> letters; //unordered map for storing the characters in t that we need to check for in s
		for (auto c : t) letters[c]++;
		int count = 0; //counts number of t's letters in current window
		int low = 0, min_length = INT_MAX, min_start = 0;
		for (int high = 0; high < s.length(); high++) {
			if (letters[s[high]] > 0) { count++; } //means that this letter is in t   
			letters[s[high]]--; //reduce the count for the letter on which we are currently 
			if (count == t.length()) { //if current windows contains all of the letters in t
				while (low < high && letters[s[low]] < 0) { letters[s[low]]++, low++; } //move low ahead if its not of any significance
				if (min_length > high - low) { min_length = high - (min_start = low) + 1; } //update the min length
				letters[s[low++]]++; //move low ahaead and also increment the value
				count--; //count-- as we are moving low ahead & low pointed to a char in t before
			}
		}
		return min_length == INT_MAX ? "" : s.substr(min_start, min_length); //check for edge case & return the result
	}
};

	