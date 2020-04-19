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


/*
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


/*
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