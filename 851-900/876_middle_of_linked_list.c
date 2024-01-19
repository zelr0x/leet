/**
 * Problem: https://leetcode.com/problems/middle-of-the-linked-list
 *
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
 
typedef struct ListNode ListNode;

ListNode* middleNode(const ListNode *const head) {
    ListNode *a = head;
    ListNode *b = head;
    while (a && a->next) {
        a = a->next->next;
        b = b->next;
    }
    return b;
}
