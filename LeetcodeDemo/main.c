//
//  main.c
//  LeetcodeDemo
//
//  Created by njim3 on 2018/7/7.
//

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* createList(int* arr, int length) {
    struct ListNode* head = NULL, * cursorNodep = NULL;
    
    for (int i = 0; i < length; ++i) {
        struct ListNode* nodep = (struct ListNode*)malloc(sizeof(struct ListNode));
        
        nodep->val = arr[i];
        nodep->next = NULL;
        
        if (i == 0) {
            head = nodep;
            cursorNodep = head;
        } else {
            cursorNodep->next = nodep;
            cursorNodep = cursorNodep->next;
        }
    }
    
    return head;
}

void traverseList(struct ListNode* head) {
    int count = 0;
    while (head != NULL) {
        printf("%d%s", head->val, head->next ? "->" : "");
        
        head = head->next;
        ++count;
    }
    
    printf("\nCount: %d\n", count);
}

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* createTree(int* arr, int index, int length) {
    struct TreeNode* pNode = NULL;
    
    if (index < length && arr[index] != -1) {
        pNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        
        if (pNode == NULL)
            return NULL;
        
        pNode->val = arr[index];
        pNode->left = createTree(arr, 2 * index + 1, length);
        pNode->right = createTree(arr, 2 * index + 2, length);
    }
    
    return pNode;
}

void preorderTraverse(struct TreeNode* root) {
    if (root == NULL)
        return ;
    
    printf("%d ", root->val);
    
    preorderTraverse(root->left);
    preorderTraverse(root->right);
}

#define STACK_INIT_SIZE         1000
#define STACK_INCREMENT         100

typedef struct TreeNodeStack {
    struct TreeNode** base;
    
    int top;
    int size;
} TreeNodeStack;

TreeNodeStack* createStack(void) {
    TreeNodeStack* stack = (TreeNodeStack*)malloc(
                                                  sizeof(struct TreeNodeStack));
    
    if (!stack)
        return NULL;
    
    stack->base = (struct TreeNode**)malloc(sizeof(struct TreeNode*) *
                                            STACK_INIT_SIZE);
    
    if (!stack->base)
        return NULL;
    
    stack->top = 0;
    stack->size = STACK_INIT_SIZE;
    
    return stack;
}

bool enlargeStack(TreeNodeStack* stack) {
    int newSize = stack->size + STACK_INCREMENT;
    
    stack->base = (struct TreeNode**)realloc(stack->base,
                                             sizeof(struct TreeNode*) * newSize);
    if (!stack->base)
        return false;
    
    stack->size = newSize;
    
    return true;
}

void pushStack(TreeNodeStack* stack, struct TreeNode* node) {
    if (stack->top >= stack->size) {
        if (!enlargeStack(stack))
            return ;
    }
    
    stack->base[stack->top++] = node;
}

struct TreeNode* popStack(TreeNodeStack* stack) {
    if (stack->top == 0)
        return NULL;
    
    return stack->base[--stack->top];
}

bool isStackEmpty(TreeNodeStack* stack) {
    return stack->top == 0;
}

int sizeOfStack(TreeNodeStack* stack) {
    return stack->top;
}

void destroyStack(TreeNodeStack* stack) {
    free(stack->base);
    free(stack);
}

typedef struct TreeStackQueue {
    struct TreeNodeStack* stack1;
    struct TreeNodeStack* stack2;
} TreeStackQueue;

TreeStackQueue* createQueue(void) {
    TreeStackQueue* queue = (TreeStackQueue*)malloc(sizeof(TreeStackQueue));
    
    if (!queue)
        return NULL;
    
    queue->stack1 = createStack();
    queue->stack2 = createStack();
    
    return queue;
}

void enQueue(TreeStackQueue* queue, struct TreeNode* node) {
    pushStack(queue->stack1, node);
}

struct TreeNode* deQueue(TreeStackQueue* queue) {
    if (isStackEmpty(queue->stack2)) {
        while (!isStackEmpty(queue->stack1)) {
            struct TreeNode* node = popStack(queue->stack1);
            
            pushStack(queue->stack2, node);
        }
    }
    
    return popStack(queue->stack2);
}

bool isQueueEmpty(TreeStackQueue* queue) {
    return isStackEmpty(queue->stack1) && isStackEmpty(queue->stack2);
}

int sizeOfQueue(TreeStackQueue* queue) {
    return sizeOfStack(queue->stack1) + sizeOfStack(queue->stack2);
}

void destroyQueue(TreeStackQueue* queue) {
    free(queue->stack1->base);
    free(queue->stack1);
    free(queue->stack2->base);
    free(queue->stack2);
}


/*
 * 7. Reverse Integer
 */
int reverse(int x) {
    int negtive = 0;
    
    // 判断正负数
    if (x == 0)
        return 0;
    else if (x < 0) {
        negtive = 1;
        x = -x;
    }
    
    int reverseNum = 0;
    
    do {
        int temp = reverseNum;
        reverseNum = reverseNum * 10 + x % 10;
        
        if (((reverseNum - x % 10) / 10) != temp)   // 溢出
            return 0;
        
        
        x /= 10;
        
    } while (x != 0);
    
    return negtive == 1 ? -reverseNum : reverseNum;
}

/*
 * 9. Palindrome Number
 */
bool isPalindrome(int x) {
    if (x < 0)
        return false;
    
    int reverseNum = 0, xcopy = x;
    
    do {
        int temp = reverseNum;
        
        reverseNum = reverseNum * 10 + x % 10;
        if ((reverseNum - x % 10) / 10 != temp)
            return false;
        
        x /= 10;
    } while (x != 0);
    
    if (reverseNum == xcopy)
        return true;
    
    return false;
}

/*
 * 13. Roman to Integer
 */

int romanVal(char ch) {
    switch (ch) {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
            
        default:
            return 0;
    }
    
    return 0;
}

int romanToInt(char* s) {
    unsigned long strLen = strlen(s);
    
    if (s == NULL || strLen == 0)
        return 0;
    
    int val = 0;
    
    for (int i = 0; i < strLen - 1; ++i) {
        int curChVal = romanVal(s[i]);
        int nextChVal = romanVal(s[i + 1]);
        
        if (curChVal < nextChVal) {
            val -= curChVal;
        } else
            val += curChVal;
    }
    
    val += romanVal(s[strLen - 1]);
    
    
    return val;
}

/*
 * 14. Longest Common Prefix
 */
char* longestCommonPrefix(char** strs, int strsSize) {
    if (strsSize == 0)
        return "";
    
    if (strsSize == 1)
        return strs[0];
    
    long minStrIndex = 0, minStrSize = strlen(strs[0]);
    
    for (int i = 1; i < strsSize; ++i) {
        unsigned long curStrLen = strlen(strs[i]);
        
        if (curStrLen == 0)
            return "";
        
        if (curStrLen < minStrSize) {
            minStrSize = curStrLen;
            
            minStrIndex = i;
        }
    }
    
    long stopIndex = minStrSize;
    for (int i = 0; i < minStrSize; ++i) {
        
        char zeroStrCurCh = strs[0][i];
        bool curLoopRes = true;
        
        for (int j = 1; j < strsSize; ++j) {
            if (zeroStrCurCh != strs[j][i])
                curLoopRes = false;
        }
        
        if (curLoopRes == false) {
            stopIndex = i;
            
            break;
        }
    }
    
    if (stopIndex == -1 || stopIndex == 0)
        return "";
    
    char* resStr = (char*)malloc(sizeof(char) * (stopIndex + 1));
    resStr[stopIndex] = '\0';
    
    strncpy(resStr, strs[minStrIndex], stopIndex);
    
    return resStr;
}

/*
 * 20. Valid Parentheses
 * URL: https://leetcode.com/problems/valid-parentheses/
 */
bool isMatch(char curCh, char topCh) {
    if ((curCh == ']' && topCh == '[') ||
        (curCh == '}' && topCh == '{') ||
        (curCh == ')' && topCh == '('))
        return true;
    
    return false;
}

bool isValid(char* s) {
    unsigned long strLen = strlen(s);
    
    if (strLen == 0)
        return true;
    
    if (strLen % 2 == 1)
        return false;
    
    char* stackArr = (char*)malloc(sizeof(char) * (strLen / 2));
    int cursor = -1;
    
    for (int i = 0; i < strLen; ++i) {
        char curCh = s[i];
        char topCh = ((cursor == -1) ? '\0' : stackArr[cursor]);
        bool isMatchRes = isMatch(curCh, topCh);
        
        if (isMatchRes) {
            stackArr[cursor--] = '\0';
        } else {
            if (++cursor >= (strLen / 2))
                return false;
            
            stackArr[cursor] = curCh;
        }
    }
    
    if (cursor == -1)
        return true;
    
    return false;
}

/*
 * 21. Merge Two Sorted Lists
 * URL: https://leetcode.com/problems/merge-two-sorted-lists/
 */
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    if (l1 == NULL || l2 == NULL) {
        return l1 == NULL ? l2 : l1;
    }
    
    struct ListNode* nodep = l1->val > l2->val ? l2 : l1;
    struct ListNode* lastPriorNodep = NULL;
    
    while (l1 != NULL && l2 != NULL) {
        if (l1->val > l2->val) {
            if (l2->next != NULL && l2->next->val >= l1->val) {
                struct ListNode* tmpNodep = l1->next;
                
                l1->next = l2->next;
                l2->next = l1;
                
                l1 = tmpNodep;
            } else {
                if (l2->next == NULL)
                    lastPriorNodep = l2;
                
                l2 = l2->next;
            }
        } else {
            if (l1->next != NULL && l1->next->val >= l2->val) {
                struct ListNode* tmpNodep = l2->next;
                
                l2->next = l1->next;
                l1->next = l2;
                
                l2 = tmpNodep;
            } else {
                if (l1->next == NULL)
                    lastPriorNodep = l1;
                
                l1 = l1->next;
            }
        }
    }
    
    if (lastPriorNodep) {
        while (lastPriorNodep->next) {
            lastPriorNodep = lastPriorNodep->next;
        }
        
        if (l1 == NULL) {
            lastPriorNodep->next = l2;
        } else if (l2 == NULL) {
            lastPriorNodep->next = l1;
        }
    }
    
    return nodep;
}

/*
 * 26. Remove Duplicates from Sorted Array
 * URL: https://leetcode.com/problems/remove-duplicates-from-sorted-array/
 */
int removeDuplicates(int* nums, int numsSize) {
    if (nums == NULL || numsSize == 0)
        return 0;
    
    if (numsSize == 1)
        return 1;
    
    int arrCount = 0;
    
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] != nums[i + 1]) {
            nums[arrCount++] = nums[i];
        } else {
            while (nums[i] == nums[i + 1])
                ++i;
            
            nums[arrCount++] = nums[i];
        }
    }
    
    return arrCount;
}

/*
 * 27. Remove Element
 * URL: https://leetcode.com/problems/remove-element/
 */
int removeElement(int* nums, int numsSize, int val) {
    int arrCount = 0;
    
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] != val) {
            nums[arrCount++] = nums[i];
        } else {
            while (nums[i] == val) {
                ++i;
            }
            
            if (i < numsSize) {
                nums[arrCount++] = nums[i];
            }
        }
    }
    
    return arrCount;
}

/*
 * 28. Implement strStr()
 * URL: https://leetcode.com/problems/implement-strstr/
 */
int strStr(char* haystack, char* needle) {
    unsigned long hLength = strlen(haystack);
    unsigned long nLength = strlen(needle);
    
    if (nLength == 0)
        return 0;
    
    if (hLength < nLength)
        return -1;
    
    int i = 0, j = 0, res = -1;
    
    while (i < hLength && j < nLength) {
        if (haystack[i] == needle[j]) {
            if (j == 0)
                res = i;
            
            ++i;
            ++j;
        } else {
            ++i;
            j = 0;
            
            if (res != -1) {
                i = res + 1;    // 匹配部分
                res = -1;
            }
        }
    }
    
    if (j == nLength)
        return res;
    
    return -1;
}

/*
 * 35. Search Insert Position
 * URL: https://leetcode.com/problems/search-insert-position/
 */
int searchInsert(int* nums, int numsSize, int target) {
    if (numsSize == 0) {
        return -1;
    }
    
    for (int i = 0; i < numsSize; ++i) {
        if ((nums[i] - target) >= 0)
            return i;
    }
    
    return numsSize;
}

/*
 * 38. Count and Say
 * URL: https://leetcode.com/problems/count-and-say/
 */
char* countAndSay(int n) {
    if (n == 1)
        return "1";
    
    // 初始结果，即当n=1时
    char* curRes = malloc(sizeof(char) * 2);
    curRes[0] = '1';
    curRes[1] = 0;

    for (int i = 2; i <= n; ++i) {
        unsigned long length = strlen(curRes);
        char* temp = (char*)malloc(sizeof(char) * length * 3);
        
        memset(temp, 0, 3 * length);    // 声明的长度为当前长度*3，以防溢出
        int count = 1, cursor = 0;      // count为当前数字的数量，cursor为结果数组的指针
        
        for (int index = 1; index < length; ++index) {
            if (curRes[index] == curRes[index - 1]) {   // 判断当前和前面的是否相同，相同则计数，不同则赋值
                ++count;
            } else {
                // 置位置
                temp[cursor++] = count + '0';
                temp[cursor++] = curRes[index - 1];
                
                count = 1;
            }
        }
        
        // 循环结束后，最后需要对结尾字符进行赋值
        temp[cursor++] = count + '0';
        temp[cursor] = curRes[length - 1];
        free(curRes);
        
        curRes = temp;
    }
    
    return curRes;
}

/*
 * 53. Maximum Subarray
 * URL: https://leetcode.com/problems/maximum-subarray/
 */
int maxSubArray(int* nums, int numsSize) {
    if (numsSize <= 0)
        return 0;
    
    int maxSum = nums[0];       // 初始设置第一个最大
    int sum = 0;                // 子串的sum
    
    for (int i = 0; i < numsSize; ++i) {
        sum += nums[i];
        maxSum = maxSum > sum ? maxSum : sum;
        
        if (sum < 0)        // 如果子串和小于0，那必有array[k...j]大于0，此处重新计数
            sum = 0;
    }
    
    return maxSum;
}

/*
 * 58. Length of Last Word
 * URL: https://leetcode.com/problems/length-of-last-word/
 */
int lengthOfLastWord(char* s) {
    
    if (s == NULL)
        return 0;
    
    int len = (int)strlen(s);
    int wordLen = 0;
    bool isPassCh = false;       // 是否找到第一个非空格字符
    
    for (int i = len - 1; i >= 0; --i) {
        if (s[i] == ' ') {
            if (isPassCh) {
                break;
            } else {
                continue;
            }
        }
        
        isPassCh = true;
        ++wordLen;
    }
    
    return wordLen;
}

/*
 * 66. Plus One
 * URL: https://leetcode.com/problems/plus-one/
 */
int* plusOne(int* digits, int digitsSize, int* returnSize) {
    if (digitsSize == 0)
        return NULL;
    
    bool needCarry = false;
    
    for (int i = digitsSize - 1; i >= 0; --i) {
        int curRes = digits[i] + ((i == digitsSize - 1) ? 1 : 0) + (needCarry ? 1 : 0);
        
        if (curRes >= 10) {
            needCarry = true;
            digits[i] = curRes % 10;
        } else {
            needCarry = false;
            digits[i] = curRes;
        }
    }
    
    *returnSize = needCarry ? digitsSize + 1 : digitsSize;
    int* returnDigits = (int*)malloc(sizeof(int) * (*returnSize));
    
    for (int i = 0; i < digitsSize; ++i) {
        if (needCarry) {
            if (i == 0) {
                returnDigits[0] = 1;
                returnDigits[1] = 0;
            } else {
                returnDigits[i + 1] = digits[i];
            }
            
        } else {
            returnDigits[i] = digits[i];
        }
    }
    
    return returnDigits;
}

/*
 * 67. Add Binary
 * URL: https://leetcode.com/problems/add-binary/
 */
char* addBinary(char* a, char* b) {
    int aLen = (int)strlen(a);
    int bLen = (int)strlen(b);
    
    if (aLen == 0 || bLen == 0)
        return aLen == 0 ? b : a;
    
    int len = aLen > bLen ? aLen : bLen;
    int* aIntp = (int*)malloc(sizeof(int) * len);
    int* bIntp = (int*)malloc(sizeof(int) * len);
    
    for (int i = 0; i < len; ++i) {
        int aStrIndex = aLen - 1 - i;
        int bStrIndex = bLen - 1 - i;
        
        aIntp[i] = aStrIndex < 0 ? 0 : a[aStrIndex] - '0';
        bIntp[i] = bStrIndex < 0 ? 0 : b[bStrIndex] - '0';
    }
    
    // add two int array
    bool carry = false;
    
    for (int i = 0; i < len; ++i) {
        int tmpRes = aIntp[i] + bIntp[i] + (carry ? 1 : 0);
        
        if (tmpRes >= 2) {
            carry = true;
            
            aIntp[i] = tmpRes % 2;
        } else {
            carry = false;
            
            aIntp[i] = tmpRes;
        }
    }
    
    int resLen = carry ? len + 1 : len;
    char* resCh = (char*)malloc(sizeof(char) * (resLen + 1));
    resCh[resLen] = '\0';
    
    if (carry) {
        resCh[0] = '1';
    }
    
    for (int i = len - 1, j = 0; i >= 0; --i, ++j) {
        resCh[(carry ? j + 1 : j)] = aIntp[i] + '0';
    }
    
    free(aIntp);
    free(bIntp);
    
    return resCh;
}

/*
 * 69. Sqrt(x)
 * URL: https://leetcode.com/problems/sqrtx/
 */
int mySqrt(int x) {
    int xAbso = x < 0 ? -x : x;
    
    if (xAbso == 0 || xAbso == 1)
        return x;
    
    long i = 1;
    while (i * i <= xAbso)
        ++i;
    
    return (int)i - 1;
}

/*
 * 70. Climbing Stairs
 * URL: https://leetcode.com/problems/climbing-stairs/
 */
int climbStairs(int n) {
    if (n == 0 || n == 1 || n == 2)
        return n;
    
    int prior = 1, behind = 2, ways = 0;
    
    for (int i = 3; i <= n; ++i) {
        ways = prior + behind;
        
        prior = behind;
        behind = ways;
    }
    
    return ways;
}

/*
 * 83. Remove Duplicates from Sorted List
 * URL: https://leetcode.com/problems/remove-duplicates-from-sorted-list/
 */
struct ListNode* deleteDuplicates(struct ListNode* head) {
    if (head == NULL)
        return NULL;
    
    if (head->next == NULL)
        return head;
    
    struct ListNode* prior = head;
    struct ListNode* current = head->next;
    
    do {
        int priorVal = prior->val, currentVal = current->val;
        
        if (priorVal == currentVal) {   // delete current node
            struct ListNode* tmpCurrentNode = current;
            
            prior->next = current->next;
            current = current->next;
            
            free(tmpCurrentNode);
        } else {
            prior = current;
            current = current->next;
        }
        
    } while (current != NULL);
    
    return head;
}

/*
 * 88. Merge Sorted Array
 * URL: https://leetcode.com/problems/merge-sorted-array/
 */
void merge(int* nums1, int m, int* nums2, int n) {
//    int nums1Len = strlen(nums1);
//
//    if (nums1Len < (m + n))
//        return ;
    
    int nIndex = 0;
    int insertPos = 0;
    
    while (nIndex < n) {
        while (insertPos < m) {
            if (nums2[nIndex] < nums1[insertPos])
                break;
            
            ++insertPos;
        }
        
        if (insertPos == m)
            break;
        
        // insert
        for (int i = m - 1; i >= insertPos; --i) {
            nums1[i + 1] = nums1[i];
        }
        
        nums1[insertPos] = nums2[nIndex++];
        ++m;
    }
    
    if (insertPos == m && nIndex < n) {
        while (nIndex < n) {
            nums1[insertPos++] = nums2[nIndex++];
        }
    }
}

/*
 * 100. Same Tree
 * URL: https://leetcode.com/problems/same-tree/
 */
bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
    if (p == NULL && q == NULL)
        return true;
    else if (p == NULL || q == NULL)
        return false;
    
    if (p->val != q->val)
        return false;
    
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

/*
 * 101. Symmetric Tree
 * URL: https://leetcode.com/problems/symmetric-tree/
 */
bool isSym(struct TreeNode* left, struct TreeNode* right) {
    if (left == NULL && right == NULL)
        return true;
    else if (left == NULL || right == NULL)
        return false;
    
    if (left->val != right->val)
        return false;
    
    return isSym(left->left, right->right) && isSym(left->right, right->left);
}

bool isSymmetric(struct TreeNode* root) {
    if (root == NULL)
        return true;
    
    return isSym(root->left, root->right);
}

/*
 * 107. Binary Tree Level Order Traversal II
 * URL: https://leetcode.com/problems/binary-tree-level-order-traversal-ii/
 */
int** levelOrderBottom(struct TreeNode* root, int** columnSizes, int* returnSize) {
    if (!root) {
        (* columnSizes) = NULL;
        (* returnSize) = 0;
        
        return NULL;
    }
    
    TreeStackQueue* queue = createQueue();
    
    TreeNodeStack* nodesValueStack = createStack();
    TreeNodeStack* nodesCountStack = createStack();
    
    enQueue(queue, root);
    int nodesCount = 1;
    struct TreeNode* treeNode = NULL;
    
    while (!isQueueEmpty(queue)) {
        nodesCount = sizeOfQueue(queue);
        
        pushStack(nodesCountStack, (struct TreeNode*)(intptr_t)nodesCount);
        
        for (int i = 0; i < nodesCount; ++i) {
            treeNode = deQueue(queue);
            
            if (treeNode->left)
                enQueue(queue, treeNode->left);
            if (treeNode->right)
                enQueue(queue, treeNode->right);
            
            pushStack(nodesValueStack, (struct TreeNode*)(intptr_t)treeNode->val);
        }
    }
    
    (* returnSize) = sizeOfStack(nodesCountStack);
    (* columnSizes) = (int*)malloc(sizeof(int) * (* returnSize));
    
    int** returnArray = (int**)malloc(sizeof(int*) * (* returnSize));
    int j = 0;
    
    while (!isStackEmpty(nodesCountStack)) {
        nodesCount = (int)(intptr_t)popStack(nodesCountStack);
        (* columnSizes)[j] = nodesCount;
        
        int* curValArr = (int*)malloc(sizeof(int) * nodesCount);
        
        for (int i = nodesCount - 1; i >=0; --i)
            curValArr[i] = (int)(intptr_t)popStack(nodesValueStack);
        
        returnArray[j] = curValArr;
        
        ++j;
    }
    
    destroyStack(nodesCountStack);
    destroyStack(nodesValueStack);
    destroyQueue(queue);
    
    return returnArray;
}

/*
 * 104. Maximum Depth of Binary Tree
 * URL: https://leetcode.com/problems/maximum-depth-of-binary-tree/
 */
int maxDepth(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    
    int leftHeight = maxDepth(root->left);
    int rightHeight = maxDepth(root->right);
    
    return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}


/*
 * 108. Convert Sorted Array to Binary Search Tree
 * URL: https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
 */
struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
    if (numsSize == 0)
        return NULL;
    
    if (numsSize == 1) {
        struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        
        node->val = nums[0];
        node->left = NULL;
        node->right = NULL;
        
        return node;
    }
    
    int low = 0, high = numsSize;
    
    int mid = (low + high) / 2;
    struct TreeNode* root;
    
    if (low < high) {
        root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        
        root->val = nums[mid];
        root->left = sortedArrayToBST(nums, mid);
        root->right = sortedArrayToBST(nums + mid + 1, numsSize - mid - 1);
    } else
        root = NULL;
    
    return root;
}

/*
 * 110. Balanced Binary Tree
 * URL: https://leetcode.com/problems/balanced-binary-tree/
 */
bool isBalanced(struct TreeNode* root) {
    if (root == NULL)
        return true;
    
    return abs(maxDepth(root->left) - maxDepth(root->right)) > 1 ? false :
    (isBalanced(root->left) && isBalanced(root->right));
}

/*
 * 111. Minimum Depth of Binary Tree
 * URL: https://leetcode.com/problems/minimum-depth-of-binary-tree/
 */
int minDepth(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    
    int leftHeight = minDepth(root->left);
    int rightHeight = minDepth(root->right);
    
    if (leftHeight == 0)
        return rightHeight + 1;
    if (rightHeight == 0)
        return leftHeight + 1;
    
    return leftHeight > rightHeight ? rightHeight + 1 : leftHeight + 1;
}

/*
 * 112. Path Sum
 * URL: https://leetcode.com/problems/path-sum/
 */
bool hasPathSum(struct TreeNode* root, int sum) {
    if (root == NULL)
        return false;
    
    if (root->left == NULL && root->right == NULL && root->val == sum)
        return true;
    
    return hasPathSum(root->left, sum - root->val) ||
            hasPathSum(root->right, sum - root->val);
}

/*
 * 118. Pascal's Triangle
 * URL: https://leetcode.com/problems/pascals-triangle/
 */
int** generate(int numRows, int** columnSizes) {
    if (numRows == 0) {
        (*columnSizes) = NULL;
        
        return NULL;
    }
    
    *columnSizes = (int*)malloc(sizeof(int) * numRows);
    int** returnArr = (int**)malloc(sizeof(int*) * numRows);
    
    for (int i = 0; i < numRows; ++i) {
        int curRowLen = i + 1;
        (*columnSizes)[i] = curRowLen;
        
        (*(returnArr + i)) = (int*)malloc(sizeof(int) * curRowLen);
        
        if (i == 0) {
            (*(returnArr + i))[0] = 1;
        } else {
            (*(returnArr + i))[0] = (*(returnArr + i))[curRowLen - 1] = 1;
            
            for (int j = 1; j < (curRowLen / 2 + curRowLen % 2); ++j) {
                (*(returnArr + i))[j] = (*(returnArr + i - 1))[j] +
                        (*(returnArr + i - 1))[j - 1];
                
                (*(returnArr + i))[curRowLen - 1 - j] = (*(returnArr + i))[j];
            }
        }
    }
    
    return returnArr;
}

/*
 * 119. Pascal's Triangle II
 * URL: https://leetcode.com/problems/pascals-triangle-ii/
 */
long getCombination(int n, int m) {
    long res = 1;
    
    for (int i = 1; i <= m; ++i) {
        res = (res * (n - m + i)) / i;
    }
    
    return res;
}

/*
 * 120. Pascal's Triangle II
 * URL: https://leetcode.com/problems/pascals-triangle-ii/
 */
int* getRow(int rowIndex, int* returnSize) {
    (* returnSize) = rowIndex + 1;
    int* returnArr = (int*)malloc((*returnSize) * sizeof(int));
    
    returnArr[0] = returnArr[(*returnSize) - 1] = 1;
    
    if (rowIndex == 0) {
        returnArr[0] = 1;
        
        return returnArr;
    }
    
    for (int i = 1; i < ((*returnSize) / 2 + 1); ++i) {
        returnArr[i] = returnArr[(*returnSize) - i - 1] =
        (int)getCombination(rowIndex, i);
    }
    
    return returnArr;
}

/*
 * 121. Best Time to Buy and Sell Stock
 * URL: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
 */
int maxProfit(int* prices, int pricesSize) {
    if (prices == NULL || pricesSize < 2)
        return 0;
    
    int maxProfit = prices[1] - prices[0];
    
    for (int i = 0; i < (pricesSize - 1); ++i) {
        for (int j = i; j < pricesSize; ++j) {
            int currentProfit = prices[j] - prices[i];
            
            if (currentProfit > maxProfit)
                maxProfit = currentProfit;
        }
    }
    
    return maxProfit < 0 ? 0 : maxProfit;
}

/*
 * 125. Valid Palindrome
 * URL: https://leetcode.com/problems/valid-palindrome/
 */
bool isAlphanumeric(char ch);
bool judgeTwoChIsEqual(char ch1, char ch2);

bool isPalindrome2(char* s) {
    if (!s)
        return false;
    
    if (strlen(s) == 0)
        return true;
    
    
    int len = (int)strlen(s);
    int i = 0, j = len - 1;
    
    while (i < j) {
        if (!isAlphanumeric(s[i])) {
            ++i;
            continue;
        }
        
        if (!isAlphanumeric(s[j])) {
            --j;
            continue;
        }
        
        if (!judgeTwoChIsEqual(s[i], s[j])) {
            return false;
        }
        
        ++i;
        --j;
    }
    
    return true;
}

bool isAlpha(char ch) {
    if ((ch >= 'a' && ch <= 'z') ||
        (ch >= 'A' && ch <= 'Z'))
        return true;
    
    return false;
}

bool isAlphanumeric(char ch) {
    if ((ch >= 'a' && ch <= 'z') ||
        (ch >= 'A' && ch <= 'Z') ||
        (ch >= '0' && ch <= '9'))
        return true;
    
    return false;
}

bool judgeTwoChIsEqual(char ch1, char ch2) {
    if (ch1 == ch2)
        return true;
    
    if (isAlpha(ch1) && isAlpha(ch2)) {
        if (ch1 - ch2 == 32 || ch2 - ch1 == 32)
            return true;
    }
    
    return false;
}

/*
 * 136. Single Number
 * URL: https://leetcode.com/problems/single-number/
 */
int singleNumber(int* nums, int numsSize) {
    if (numsSize == 1) {
        return nums[0];
    }
    
    int count = 0;
    
    for (int i = 0; i < numsSize; ++i) {
        count = 0;
        
        for (int j = 0; j < numsSize; ++j) {
            if (nums[i] == nums[j])
                ++count;
        }
        
        if (count == 1)
            return nums[i];
    }
    
    return 0;
}

/*
 * 141. Linked List Cycle
 * URL: https://leetcode.com/problems/linked-list-cycle/
 */
bool hasCycle(struct ListNode *head) {
    if (!head)
        return false;
    
    struct ListNode* slow = head, * fast = head->next;
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast)
            return true;
    }
    
    return false;
}

/*
 * 160. Intersection of Two Linked Lists
 * URL: https://leetcode.com/problems/intersection-of-two-linked-lists/
 */
int getListLength(struct ListNode* head);
struct ListNode *getIntersectionNode(struct ListNode *headA,
                                     struct ListNode *headB) {
    if (!headA || !headB)
        return NULL;
    
    int listALength = getListLength(headA);
    int listBLength = getListLength(headB);
    int diff = listALength - listBLength;
    
    // 先把长的链表走完
    for (int i = 0; i < abs(diff); ++i) {
        if (diff > 0)
            headA = headA->next;
        else
            headB = headB->next;
    }
    
    // 找相同
    while (headA && headB && headA != headB) {
        headA = headA->next;
        headB = headB->next;
    }
    
    return (headA && headB) ? headA : NULL;
}

int getListLength(struct ListNode* head) {
    int length = 0;
    
    while (head) {
        ++length;
        
        head = head->next;
    }
    
    return length;
}

struct ListNode *getIntersectionNode2(struct ListNode *headA,
                                      struct ListNode *headB) {
    if (!headA || !headB)
        return NULL;
    
    struct ListNode* aNode = headA, * bNode = headB;
    
    while (aNode != bNode) {
        aNode = aNode ? aNode->next : headB;
        bNode = bNode ? bNode->next : headA;
    }
    
    return aNode;
}

/*
 * 167. Two Sum II - Input array is sorted
 * URL: https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
 */
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
    if (numbers == NULL || numbersSize == 1) {
        (* returnSize) = 0;
        
        return NULL;
    }
    
    int left = 0, right = numbersSize - 1;
    
    int* returnArr = (int*)malloc(sizeof(int) * 2);
    (* returnSize) = 2;
    
    while (left < right) {
        if ((numbers[left] + numbers[right]) == target) {
            returnArr[0] = left + 1;
            returnArr[1] = right + 1;
            
            return returnArr;
        } else if ((numbers[left] + numbers[right]) > target) {
            --right;
        } else
            ++left;
    }
    
    return NULL;
}

/*
 * 168. Excel Sheet Column Title
 * URL: https://leetcode.com/problems/excel-sheet-column-title/
 */
char *convertToTitle(int n) {
    char* str1 = (char*)malloc(sizeof(char) * 255);
    char* str2 = (char*)malloc(sizeof(char) * 255);
    
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsizeof-array-argument"
#pragma clang diagnostic ignored "-Wsizeof-pointer-memaccess"
    memset(str1, '\0', sizeof(str1));
    memset(str2, '\0', sizeof(str2));
#pragma clang diagnostic pop
    
    int count = 0;
    
    while (n > 0) {
        n = n - 1;
        
        *(str1 + count) = (n % 26) + 'A';
        ++count;
        
        n = n / 26;
    }
    
    for (int i = 0; i < strlen(str1); ++i) {
        *(str2 + i) = *(str1 + strlen(str1) - i - 1);
    }
    
    free(str1);
    
    return str2;
}

/*
 * 169. Majority Element
 * https://leetcode.com/problems/majority-element/
 */
int majorityElement(int* nums, int numsSize) {
    int* elementArr = (int*)malloc(sizeof(int) * numsSize);
    int* elementCountArr = (int*)malloc(sizeof(int) * numsSize);
    
    elementArr[0] = nums[0];
    elementCountArr[0] = 1;
    int count = 1;
    
    for (int i = 1; i < numsSize; ++i) {
        int j = 0;
        
        for (j = 0; j < count; ++j) {
            if (nums[i] == elementArr[j]) {
                elementCountArr[j] = elementCountArr[j] + 1;
                
                break;
            }
        }
        
        if (j == count) {
            elementArr[count] = nums[i];
            elementCountArr[count] = 1;
            
            ++count;
        }
    }
    
    int maxElementCount = 0, index = -1;
    for (int i = 0; i < count; ++i) {
        if (elementCountArr[i] > maxElementCount) {
            maxElementCount = elementCountArr[i];
            index = i;
        }
    }
    
    int maxCountElement = elementArr[index];
    
    free(elementArr);
    free(elementCountArr);
    
    return maxCountElement;
}

/*
 * 171. Excel Sheet Column Number
 * https://leetcode.com/problems/excel-sheet-column-number/
 */
int titleToNumber(char* s) {
    if (strlen(s) == 0)
        return 0;
    
    int result = 0;
    int len = (int)strlen(s);
    
    int j = 0;
    for (int i = len - 1; i >= 0; --i) {
        result += ((s[i] - 'A' + 1) * pow(26, j));
        
        ++j;
    }
    
    return result;
}

/*
 * 172. Factorial Trailing Zeroes
 * https://leetcode.com/problems/factorial-trailing-zeroes/
 */
int trailingZeroes(int n) {
    int fiveCount = 0;
    
    while (n != 0) {
        int tmpFiveCount = n / 5;
        
        fiveCount += tmpFiveCount;
        n = tmpFiveCount;
    }
    
    return fiveCount;
}

/*
 * 189. Rotate Array
 * https://leetcode.com/problems/rotate-array/
 */
void rotate(int* nums, int numsSize, int k) {
    if (nums == NULL || numsSize == 0 || k == 0 || (k % numsSize == 0))
        return ;
    
    k = k % numsSize;
    
    int firstNum = 0;
    
    for (int i = 0; i < k; ++i) {
        firstNum = nums[numsSize - 1];
        
        for (int j = numsSize - 2; j >= 0; --j) {
            nums[j + 1] = nums[j];
        }
        
        nums[0] = firstNum;
    }
}

void rotate2(int* nums, int numsSize, int k) {
    if (nums == NULL || numsSize == 0 || k == 0 || (k % numsSize == 0))
        return ;
    
    k = k % numsSize;
    
    int* newNums = (int*)malloc(sizeof(int) * numsSize);
    
    // store all nums to newNums array
    for (int i = 0; i < numsSize; ++i) {
        newNums[i] = nums[i];
    }
    
    // get new position and store back
    for (int i = 0; i < numsSize; ++i) {
        nums[(i + k) % numsSize] = newNums[i];
    }
    
    free(newNums);
}

void reverseRotate(int* front, int* rear);
void rotate3(int* nums, int numsSize, int k) {
    if (nums == NULL || numsSize == 0 || k == 0 || (k % numsSize == 0))
        return ;
    
    k = k % numsSize;
    
    reverseRotate(&nums[0], &nums[numsSize - k - 1]);
    reverseRotate(&nums[numsSize - k], &nums[numsSize - 1]);
    reverseRotate(&nums[0], &nums[numsSize - 1]);
}

void reverseRotate(int* front, int* rear) {
    if (front == NULL || rear == NULL)
        return ;
    
    while (front < rear) {
        int tempInt = (*front);
        
        (*front) = (*rear);
        (*rear) = tempInt;
        
        ++front;
        --rear;
    }
}

/*
 * 190. Reverse Bits
 * URL: https://leetcode.com/problems/reverse-bits/
 */
uint32_t reverseBits(uint32_t n) {
    int* binaryArr = (int*)malloc(sizeof(int) * 32);
    
    int binaryLen = 32;
    
    do {
        --binaryLen;
        binaryArr[binaryLen] = n % 2;
        
        n /= 2;
        
    } while (n != 0);
    
    // 前端置0
    for (int i = 0; i < binaryLen; ++i) {
        binaryArr[i] = 0;
    }
    
    // reverse
    int left = 0, right = 31;
    int tempInt = 0;
    
    while (left < right) {
        tempInt = binaryArr[left];
        binaryArr[left] = binaryArr[right];
        binaryArr[right] = tempInt;
        
        ++left;
        --right;
    }
    
    // 计算结果
    uint32_t result = 0;
    
    for (int i = 31; i >= 0; --i) {
        result += (binaryArr[i] * pow(2, 31 - i));
    }
    
    free(binaryArr);
    
    return result;
}

/*
 * 191. Number of 1 Bits
 * https://leetcode.com/problems/number-of-1-bits/
 */
int hammingWeight(uint32_t n) {
    int* binaryArr = (int*)malloc(sizeof(int) * 32);
    
    int binaryLen = 32;
    do {
        --binaryLen;
        binaryArr[binaryLen] = n % 2;
        
        n /= 2;
        
    } while (n != 0);
    
    // calculate 1
    int count = 0;
    for (int i = 31; i >= binaryLen; --i) {
        if (binaryArr[i] == 1)
            ++count;
    }
    
    free(binaryArr);
    
    return count;
}

/*
 * 198. House Robber
 * URL: https://leetcode.com/problems/house-robber/
 */
int max(int val1, int val2);
int rob(int* nums, int numsSize) {
    if (nums == NULL || numsSize == 0)
        return 0;
    
    if (numsSize == 1) {
        return nums[0];
    }
    
    int* maxValueArr = (int*)malloc(sizeof(int) * numsSize);
    
    maxValueArr[0] = nums[0];
    maxValueArr[1] = max(nums[0], nums[1]);
    
    for (int i = 2; i < numsSize; ++i) {
        maxValueArr[i] = max(maxValueArr[i - 2] + nums[i], maxValueArr[i - 1]);
    }
    
    int maxValue = maxValueArr[numsSize - 1];
    free(maxValueArr);
    
    return maxValue;
}

int max(int val1, int val2) {
    return val1 > val2 ? val1 : val2;
}

/*
 * 202. Happy Number
 * URL: https://leetcode.com/problems/happy-number/
 */
bool isHappy(int n) {
    int sum = 0;
    
    while (n > 0) {
        sum += pow(n % 10, 2);
        
        n /= 10;
    }
    
    if (sum >= 10)
        return isHappy(sum);
    
    if (sum == 1 || sum == 7)
        return true;
    
    return false;
}

bool isHappy2(int n) {
    int sum = 0;
    
    while (n > 0) {
        sum += pow(n % 10, 2);
        
        n /= 10;
    }
    
    if (sum == 4)
        return false;
    
    if (sum != 1)
        return isHappy2(sum);
    
    return true;
}

/*
 * 203. Remove Linked List Elements
 * URL: https://leetcode.com/problems/remove-linked-list-elements/
 */
struct ListNode* removeElements(struct ListNode* head, int val) {
    struct ListNode* prior = NULL, * current = head;
    
    while (current) {
        if (current->val == val) {
            if (prior == NULL) {        // head node
                head = current->next;
                current->next = NULL;
                
                free(current);
                
                current = head;
                prior = NULL;
                
            } else {
                if (current != NULL) {      // center node
                    prior->next = current->next;
                    current->next = NULL;
                    
                    free(current);
                    
                    current = prior->next;
                }
            }
            
        } else {
            prior = current;
            current = current->next;
        }
    }

    return head;
}

/*
 * 204. Count Primes
 * URL: https://leetcode.com/problems/count-primes/
 */
int countPrimes(int n) {
    if (n == 0 || n == 1)
        return 0;
    
    int count = 0;
    
    for (int val = 2; val < n; ++val) {
        int i = 0, j = sqrt(val);
        
        for (i = 2; i <= j; ++i) {
            if (val % i == 0)
                break;
        }
        
        if (i > j)
            ++count;
    }
    
    return count;
}

/*
 * 205. Isomorphic Strings
 * URL: https://leetcode.com/problems/isomorphic-strings/
 */
bool isIsomorphic(char* s, char* t) {
    int* hashArr = (int*)malloc(sizeof(int) * 255);
    
    // initialize
    for (int i = 0; i < 255; ++i)
        hashArr[i] = 0;
    
    for (int i = 0; s[i] != '\0'; ++i) {        // Don't use strlen(s)
        int index = s[i];
        
        if (hashArr[index] == 0) {
            for (int j = 0; j < 255; ++j) {
                if (hashArr[j] == t[i])
                    return false;
            }
            
            hashArr[index] = t[i];
        } else {
            if (hashArr[index] != t[i])
                return false;
        }
    }
    
    free(hashArr);
    
    return true;
}

/*
 * 206. Reverse Linked List
 * URL: https://leetcode.com/problems/reverse-linked-list/
 */
struct ListNode* reverseList(struct ListNode* head) {
    if (head == NULL)
        return NULL;
    
    if (head->next == NULL)
        return head;
    
    struct ListNode* current = head;
    head = head->next;
    struct ListNode* next = head->next;
    
    current->next = NULL;
    
    while (next) {
        head->next = current;
        current = head;
        head = next;
        
        next = next->next;
    }
    
    head->next = current;
    
    return head;
}

/*
 * 217. Contains Duplicate
 * URL: https://leetcode.com/problems/contains-duplicate/
 */
bool containsDuplicate(int* nums, int numsSize) {
    if (nums == NULL || numsSize == 0)
        return false;
    
    int* noDuplicateArr = (int*)malloc(sizeof(int) * numsSize);
    int* countArr = (int*)malloc(sizeof(int) * numsSize);
    
    // initialize
    for (int i = 0; i < numsSize; ++i) {
        noDuplicateArr[i] = INT_MIN;
        countArr[i] = 0;
    }
    
    for (int i = 0; i < numsSize; ++i) {
        int j = 0;
        
        for (j = 0; j <= i; ++j) {
            if (noDuplicateArr[j] == nums[i]) {
                if (countArr[j] == 1) {
                    free(noDuplicateArr);
                    free(countArr);
                    
                    return true;
                }
            }
        }
        
        if (j > i) {
            noDuplicateArr[i] = nums[i];
            countArr[i] = 1;
        }
    }
    
    free(noDuplicateArr);
    free(countArr);
    
    return false;
}

/*
 * 219. Contains Duplicate II
 * URL: https://leetcode.com/problems/contains-duplicate-ii/
 */
bool containsNearbyDuplicate(int* nums, int numsSize, int k) {
    if (nums == NULL || numsSize == 0)
        return false;
    
    for (int i = 0; i < numsSize - 1; ++i) {
        for (int j = i + 1; j < numsSize; ++j) {
            if (nums[i] == nums[j]) {
                if (j - i <= k)
                    return true;
            }
        }
    }
    
    return false;
}


/*
 * 226. Invert Binary Tree
 * URL: https://leetcode.com/problems/invert-binary-tree/
 */
struct TreeNode* invertTree(struct TreeNode* root) {
    if (!root)
        return NULL;
    
    struct TreeNode* tmpNode = root->left;
    root->left = root->right;
    root->right = tmpNode;
    
    invertTree(root->left);
    invertTree(root->right);
    
    return root;
}


/*
 * 231. Power of Two
 * URL: https://leetcode.com/problems/power-of-two/
 */
bool isPowerOfTwo(int n) {
    if (n == 0)
        return false;
    
    if (n == 1)
        return true;
    
    while (n != 1) {
        int remainder = n % 2;
        
        if (remainder != 0)
            return false;
        
        n /= 2;
    }
    
    return true;
}


/*
 * 234. Palindrome Linked List
 * URL: https://leetcode.com/problems/palindrome-linked-list/
 */
bool isListPalindrome(struct ListNode* head) {
    if (!head || !(head->next))
        return true;
    
    // use fast & slow pointer to find middle of list
    struct ListNode* fastP = head, * slowP = head;
    
    while (fastP->next && fastP->next->next) {
        fastP = fastP->next->next;
        slowP = slowP->next;
    }
    
    struct ListNode* secHalfHead = slowP->next;
    slowP->next = NULL;
    
    // reverse second half list
    struct ListNode* p1 = secHalfHead, * p2 = secHalfHead->next;
    
    while (p1 && p2) {
        struct ListNode* tmpNode = p2->next;
        
        p2->next = p1;
        p1 = p2;
        p2 = tmpNode;
    }
    
    secHalfHead->next = NULL;
    
    struct ListNode* p = p2 ? p2 : p1;
    struct ListNode* q = head;
    
    while (p) {
        if (p->val != q->val)
            return false;
        
        p = p->next;
        q = q->next;
    }
    
    return true;
}

/*
 * 235. Lowest Common Ancestor of a Binary Search Tree
 * URL: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
 */
struct TreeNode* lowestCommonAncestor(struct TreeNode* root,
                                      struct TreeNode* p, struct TreeNode* q) {
    if (root == NULL)
        return NULL;
    
    int minNum = p->val > q->val ? q->val : p->val;
    int maxNum = p->val > q->val ? p->val : q->val;
    
    if (minNum > root->val) {
        return lowestCommonAncestor(root->right, p, q);
    } else if (maxNum < root->val) {
        return lowestCommonAncestor(root->left, p, q);
    }
    
    return root;
}

/*
 * 237. Delete Node in a Linked List
 * URL: https://leetcode.com/problems/delete-node-in-a-linked-list/
 */
void deleteNode(struct ListNode* node) {
    if (!node || !(node->next))
        return ;
    
    struct ListNode* nextP = node->next;
    
    node->val = nextP->val;
    node->next = nextP->next;
    nextP->next = NULL;
    
    free(nextP);
}

/*
 * 242. Valid Anagram
 * URL: https://leetcode.com/problems/valid-anagram/
 */
bool isAnagram(char* s, char* t) {
    if ((!s || !t) || strlen(s) != strlen(t))
        return false;
    
    if (strcmp(s, t) == 0)
        return true;
    
    int sCount[26] = {0}, tCount[26] = {0};
    
    for (int i = 0; s[i] != '\0'; ++i) {
        ++sCount[s[i] - 'a'];
        ++tCount[t[i] - 'a'];
    }
    
    for (int i = 0; i < 26; ++i) {
        if (sCount[i] != tCount[i])
            return false;
    }
    
    return true;
}

/*
 * 257. Binary Tree Paths
 * URL: https://leetcode.com/problems/binary-tree-paths/
 */
int pathsNum(struct TreeNode* root);
void Traverse(struct TreeNode* root, char** array, char* spre, int* pIndex);
char** binaryTreePaths(struct TreeNode* root, int* returnSize) {
    int index = 0;
    
    if (!root)
        return NULL;
    
    int paths = (*returnSize) = pathsNum(root);
    char** pathsArray = (char**)calloc(paths, sizeof(char*));
    
    Traverse(root, pathsArray, "", &index);
    
    return pathsArray;
}

int pathsNum(struct TreeNode* root) {
    if (!root)
        return 0;
    
    if (!root->left && !root->right)
        return 1;
    
    return pathsNum(root->left) + pathsNum(root->right);
}

char* stringAdd(char* s, int val) {
    char temp[10];
    
    if (strlen(s) == 0)
        sprintf(temp, "%d", val);
    else
        sprintf(temp, "->%d", val);
    
    char* snew = (char*)calloc(strlen(s) + strlen(temp) + 1, sizeof(char));
    
    strcpy(snew, s);
    strcat(snew, temp);
    
    return snew;
}

void Traverse(struct TreeNode* root, char** array, char* spre, int* pIndex) {
    char* s;
    
    if (!root->left && !root->right) {
        s = stringAdd(spre, root->val);
        
        array[(*pIndex)++] = s;
    }
    
    if (root->left) {
        s = stringAdd(spre, root->val);
        
        Traverse(root->left, array, s, pIndex);
        free(s);
    }
    
    if (root->right) {
        s = stringAdd(spre, root->val);
        
        Traverse(root->right, array, s, pIndex);
        free(s);
    }
}

/*
 * 258. Add Digits
 * URL: https://leetcode.com/problems/add-digits/
 */
int addDigits(int num) {
    if (num == 0)
        return 0;
    
    int sum = 0;
    while (num != 0) {
        sum = 0;
        while (num != 0) {
            sum += (num % 10);
            num /= 10;
        }
        
        if (sum < 10)
            break;
        
        num = sum;
    }
    
    return sum;
}

/*
 * 263. Ugly Number
 * URL: https://leetcode.com/problems/ugly-number/
 */
bool isUgly(int num) {
    if (num == 0 || num == 1)
        return false;
    
    while (num != 1) {
        if (num % 2 == 0) {
            num /= 2;
            
            continue;
        } else if (num % 3 == 0) {
            num /= 3;
            
            continue;
        } else if (num % 5 == 0) {
            num /= 5;
            
            continue;
        }
        
        return false;
    }
    
    return true;
}

/*
 * 268. Missing Number
 * URL: https://leetcode.com/problems/missing-number/
 */
int missingNumber(int* nums, int numsSize) {
    // notice that total sum added from 1
    int sumNum = 0, totalSum = 0;
    
    for (int i = 0; i < numsSize; ++i) {
        sumNum += nums[i];
        totalSum += (i + 1);
    }
    
    return totalSum - sumNum;
}

/*
 * 278. First Bad Version
 * URL: https://leetcode.com/problems/first-bad-version/
 */
// Forward declaration of isBadVersion API.
//bool isBadVersion(int version);
//
//int firstBadVersion(int n) {
//    int left = 0, right = n;
//
//    while (left < right) {
//        int mid = left + (right - left) / 2;
//
//        if (isBadVersion(mid))
//            right = mid;
//        else
//            left = mid + 1;
//    }
//
//    return left;
//}

/*
 * 283. Move Zeroes
 * URL: https://leetcode.com/problems/move-zeroes/
 */
void moveZeroes(int* nums, int numsSize) {
    if (numsSize == 0 || numsSize == 1)
        return ;
    
    int zeroCount = 0;
    
    // from back to start, loop array
    for (int i = numsSize - 1; i >= 0; --i) {
        if (nums[i] != 0)
            continue;
        
        // find 0, move 0 to end
        ++zeroCount;
        
        int j = i;
        for (j = i; j < numsSize - zeroCount; ++j) {
            nums[j] = nums[j + 1];
        }
        
        nums[j] = 0;
    }
}

/*
 * 290. Word Pattern
 * URL: https://leetcode.com/problems/word-pattern/
 */
void split(char* src, const char* separator, char** dest, int* num);
bool wordPattern(char* pattern, char* str) {
    if (str == NULL || pattern == NULL)
        return false;
    
    int patternLen = (int)strlen(pattern);
    
    if (patternLen == 0)
        return false;
    
    // space is separator
    char* separator = " ";
    char* dest[255] = {0};
    int strSplitCount = 0;
    
    const int strLen = (int)strlen(str);
    char* strCopy = (char*)calloc(strLen, sizeof(char));
    
    memcpy(strCopy, str, sizeof(char) * strLen);
    
    split(strCopy, separator, dest, &strSplitCount);
    
    if (strSplitCount == 0 ||
        (patternLen != strSplitCount))
        return false;
    
    // Three are 26 charaters
    char** patternDictArr = (char**)calloc(26, sizeof(char*));
    
    for (int i = 0; i < patternLen; ++i) {
        char curPattern = pattern[i];
        char* curPatternArr = patternDictArr[curPattern - 'a'];
        
        if (!curPatternArr) {
            // if previous dict value is equal to dest[i], it would be false
            for (int j = 0; j < 26; ++j) {
                if (patternDictArr[j] &&
                    strcmp(patternDictArr[j], dest[i]) == 0)  {
                    return false;
                }
            }
            
            patternDictArr[curPattern - 'a'] = dest[i];
        } else {
            if (strcmp(curPatternArr, dest[i]) != 0)
                return false;
        }
    }
    
    return true;
}

void split(char* src, const char* separator, char** dest, int* num) {
    if ((src == NULL || strlen(src) == 0) ||
        (separator == NULL || strlen(separator) == 0))
        return ;
    
    int count = 0;
    char* pNext = strtok(src, separator);
    
    while (pNext) {
        *dest++ = pNext;        // (*dest) = pNext; ++dest;
        
        ++count;
        pNext = strtok(NULL, separator);
    }
    
    *num = count;
}

/*
 * 292. Nim Game
 * URL: https://leetcode.com/problems/nim-game/
 */
bool canWinNim(int n) {
    return n % 4 ? true : false;
}

/*
 * 303. Range Sum Query - Immutable
 * URL: https://leetcode.com/problems/range-sum-query-immutable/
 */
typedef struct {
    int* sumNums;
    int size;
} NumArray;

NumArray* numArrayCreate(int* nums, int numsSize) {
    NumArray* numArr = (NumArray*)malloc(sizeof(NumArray));
    
    if (!numArr)
        return NULL;
    
    numArr->sumNums = (int*)calloc(numsSize, sizeof(int));
    numArr->size = numsSize;
    
    // assign each number value
    for (int i = 0; i < numsSize; ++i) {
        int lastSum = (i == 0) ? 0 : numArr->sumNums[i - 1];
        
        numArr->sumNums[i] = lastSum + nums[i];
    }
    
    return numArr;
}

void numArrayTraverse(NumArray* obj) {
    for (int i = 0; i < obj->size; ++i) {
        printf("%d ", obj->sumNums[i]);
    }
    
    putchar('\n');
}

int numArraySumRange(NumArray* obj, int i, int j) {
    return obj->sumNums[j] - (i == 0 ? 0 : obj->sumNums[i - 1]);
}

void numArrayFree(NumArray* obj) {
    free(obj->sumNums);
    free(obj);
}

/*
 * 326. Power of Three
 * URL: https://leetcode.com/problems/power-of-three/
 */
bool isPowerOfThree(int n) {
    return n > 0 ? !(1162261467 % n) : false;
}

/*
 * 342. Power of Four
 * URL: https://leetcode.com/problems/power-of-four/
 */
bool isPowerOfFour(int num) {
    if (num < 0)
        return false;
    
    return ((num & (num - 1)) == 0) && (num - 1) % 3 == 0;
}

/*
 * 344. Reverse String
 * URL: https://leetcode.com/problems/reverse-string/
 */
void reverseString(char* s, int sSize) {
    if (sSize == 0)
        return ;
    
    char tmpCh = ' ';
    int left = 0, right = sSize - 1;
    
    while (left < right) {
        tmpCh = s[left];
        s[left] = s[right];
        s[right] = tmpCh;
        
        ++left;
        --right;
    }
}

/*
 * 345. Reverse Vowels of a String
 * URL: https://leetcode.com/problems/reverse-vowels-of-a-string/
 */
bool isCharVowel(char ch);
char* reverseVowels(char* s) {
    // vowels contain a,e,i,o,u
    if (s == NULL)
        return NULL;
    
    char tmpCh = ' ';
    int left = 0, right = (int)strlen(s) - 1;
    
    while (left <= right) {
        if (!isCharVowel(s[left])) {
            ++left;
            
            continue;
        }
        
        if (!isCharVowel(s[right])) {
            --right;
            
            continue;
        }
        
        // change
        tmpCh = s[left];
        s[left] = s[right];
        s[right] = tmpCh;
        
        ++left;
        --right;
    }
    
    return s;
}

bool isCharVowel(char ch) {
    if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
        ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U')
        return true;
    
    return false;
}

/*
 * 349. Intersection of Two Arrays
 * URL: https://leetcode.com/problems/intersection-of-two-arrays/
 */
int comp(const void* a, const void* b);
int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size,
                  int* returnSize) {
    int shortSize = nums1Size > nums2Size ? nums2Size : nums1Size;
    int* returnNums = (int*)calloc(shortSize, sizeof(int));
    
    (*returnSize) = 0;
    
    // sort using qsort
    qsort(nums1, nums1Size, sizeof(int), comp);
    qsort(nums2, nums2Size, sizeof(int), comp);
    
    for (int i = 0, j = 0; i < nums1Size && j < nums2Size;) {
        while (i < nums1Size && nums1[i] < nums2[j])
            ++i;
        
        if (nums1[i] == nums2[j]) {
            returnNums[*returnSize] = nums1[i];
            
            // remove duplicate
            while (i < nums1Size && nums1[i] == returnNums[*returnSize])
                ++i;
            while (j< nums2Size && nums2[j] == returnNums[*returnSize])
                ++j;
            
            ++(*returnSize);
        }
        
        while (j < nums2Size && nums2[j] < nums1[i])
            ++j;
    }
    
    return returnNums;
}

int comp(const void* a, const void* b) {
    return *(int*)a > *(int*)b;
}

/*
 * 350. Intersection of Two Arrays II
 * URL: https://leetcode.com/problems/intersection-of-two-arrays-ii/
 */
int compareInt(const void* a, const void* b);
int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size,
               int* returnSize) {
    int shortSize = nums1Size > nums2Size ? nums2Size : nums1Size;
    int* returnNums = (int*)calloc(shortSize, sizeof(int));
    
    (*returnSize) = 0;
    
    // sort using qsort
    qsort(nums1, nums1Size, sizeof(int), compareInt);
    qsort(nums2, nums2Size, sizeof(int), compareInt);
    
    int i = 0, j = 0;
    while (i < nums1Size && j < nums2Size) {
        if (nums1[i] == nums2[j]) {
            returnNums[(*returnSize)] = nums1[i];
            
            ++i;
            ++j;
            ++(*returnSize);
        } else if (nums1[i] < nums2[j])
            ++i;
        else
            ++j;
    }
    
    return returnNums;
}

int compareInt(const void* a, const void* b) {
    if ((*(int*)a) == (*(int*)b))
        return 0;
    
    return (*(int*)a) > (*(int*)b) ? 1: -1;
}

/*
 * 367. Valid Perfect Square
 * URL: https://leetcode.com/problems/valid-perfect-square/
 */
bool isPerfectSquare(int num) {
    if (num == 1)
        return true;
    
    unsigned long left = 1, right = num;
    unsigned long middle = num / 2;
    
    while (true) {
        if (middle * middle > num) {
            if ((middle - 1) * (middle - 1) < num)
                return false;
            
            right = middle;
            middle = (left + right) / 2;
        } else if (middle * middle < num) {
            if ((middle + 1) * (middle + 1) > num)
                return false;
            
            left = middle;
            middle = (left + right) / 2;
        } else
            break;
    }
    
    return true;
}

bool isPerfectSquare2(int num) {
    if (num == 1)
        return true;
    
    unsigned long left = 1, right = num;
    
    while (left < right) {
        unsigned long middle = (left + right) / 2;
        
        if (middle * middle > num) {
            right = middle;
        } else if (middle * middle < num) {
            left = middle;
        } else
            return true;
        
        if ((left * left) < num && (right * right) > num &&
            (right - left == 1))
            return false;
    }
    
    return false;
}

/*
 * 371. Sum of Two Integers
 * URL: https://leetcode.com/problems/sum-of-two-integers/
 */
int getSum(int a, int b) {
    while (b) {
        int c = a ^ b;
        b = (a & b) << 1;
        a = c;
    }
    
    return a;
}

/*
 * 383. Ransom Note
 * URL: https://leetcode.com/problems/ransom-note/
 */
bool canConstruct(char* ransomNote, char* magazine) {
    int* countArr = (int*)calloc(26, sizeof(int));
    int count = 0;
    int ransomSize = (int)strlen(ransomNote);
    int magzaineSize = (int)strlen(magazine);
    
    for (int i = 0; i < ransomSize; ++i) {
        ++countArr[ransomNote[i] - 'a'];
        
        ++count;
    }
    
    for (int i = 0; i < magzaineSize && count > 0; ++i) {
        if (countArr[magazine[i] - 'a'] > 0) {
            --countArr[magazine[i] - 'a'];
            
            --count;
        }
    }
    
    free(countArr);
    
    if (count)
        return false;
    
    return true;
}

/*
 * 387. First Unique Character in a String
 * URL: https://leetcode.com/problems/first-unique-character-in-a-string/
 */
int firstUniqChar(char* s) {
    int strSize = (int)strlen(s);
    if (strSize == 0)
        return -1;
    
    int* countArr = (int*)calloc(26, sizeof(int));
    
    for (int i = 0; i < strSize; ++i)
        ++countArr[s[i] - 'a'];
    
    int index = -1;
    for (int i = 0; i < strSize; ++i) {
        if (countArr[s[i] - 'a'] == 1) {
            index = i;
            break;
        }
    }
    
    free(countArr);
    return index;
}

/*
 * 389. Find the Difference
 * URL: https://leetcode.com/problems/find-the-difference/
 */
char findTheDifference(char* s, char* t) {
    int sSize = (int)strlen(s), tSize = (int)strlen(t);
    int* countArr = (int*)calloc(26, sizeof(int));
    
    for (int i = 0; i < tSize; ++i)
        ++countArr[t[i] - 'a'];
    
    for (int i = 0; i < sSize; ++i)
        --countArr[s[i] - 'a'];
    
    int index = -1;
    
    for (int i = 0; i < 26; ++i) {
        if (countArr[i] == 1) {
            index = i;
            
            break;
        }
    }
    
    return index + 'a';
}

/*
 * 400. Nth Digit
 * URL: https://leetcode.com/problems/nth-digit/
 */
int findNthDigit(int n) {
    // confirm scope
    int digit = 1;
    int remain = 0;
    int tempN = n;
    
    while (true) {
        remain = tempN - 9 * pow(10, digit - 1) * digit;
        
        if (remain <= 0) {
            remain = tempN;
            break;
        }
        
        ++digit;
        tempN = remain;
    }
    
    // calculate the number
    int theNum = (remain - 1) / digit + pow(10, digit - 1);
    int pos = (remain - 1) % digit;
    int nThDigit = theNum / (int)pow(10, digit - pos - 1) % 10;
    
    return nThDigit ;
}

/*
 * 401. Binary Watch
 * URL: https://leetcode.com/problems/binary-watch/
 */
int countOne(int num);
char** readBinaryWatch(int num, int* returnSize) {
    if (num == 0) {
        (*returnSize) = 1;
        
        char** resultArr = (char**)calloc(1, sizeof(char*));
        
        resultArr[0] = (char*)calloc(6, sizeof(char));
        resultArr[0] = "0:00";
        
        return resultArr;
    }
    
    char** resultArr = (char**)calloc(1000, sizeof(char*));
    int hourOneNum = 0, minOneNum = 0, totalOneNum = 0;
    int count = 0;
    
    for (int i = 0; i < 12; ++i) {
        hourOneNum = countOne(i);
        
        for (int j = 0; j < 60; ++j) {
            minOneNum = countOne(j);
            totalOneNum = hourOneNum + minOneNum;
            
            if (totalOneNum == num) {
                // save
                resultArr[count] = (char*)calloc(6, sizeof(char*));
                sprintf(resultArr[count], "%d:%02d", i, j);
                ++count;
            }
        }
    }
    
    (*returnSize) = count;
    
    return resultArr;
}

int countOne(int num) {
    int oneNum = 0;
    
    while (num) {
        oneNum += num & 1;
        num >>= 1;
    }
    
    return oneNum;
}

/*
 * 404. Sum of Left Leaves
 * URL: https://leetcode.com/problems/sum-of-left-leaves/
 */
void traverseLeft(struct TreeNode* node, int* sum, bool isLeft);
int sumOfLeftLeaves(struct TreeNode* root) {
    int sum = 0;
    
    traverseLeft(root, &sum, false);
    
    return sum;
}
void traverseLeft(struct TreeNode* node, int* sum, bool isLeft) {
    if (!node)
        return ;
    
    if (node->left == NULL && node->right == NULL && isLeft) {
        (*sum) += node->val;
        
        return ;
    }
    
    traverseLeft(node->left, sum, true);
    traverseLeft(node->right, sum, false);
}

/*
 * 405. Convert a Number to Hexadecimal
 * URL: https://leetcode.com/problems/convert-a-number-to-hexadecimal/
 */
int getHexSize(int num);
char* toHex(int num) {
    uint32_t uNum = num;
    int hexSize = getHexSize(uNum);
    
    char* hexStr = (char*)calloc(hexSize + 1, sizeof(char));
    hexStr[hexSize] = '\0';
    
    if (uNum == 0) {
        hexStr[0] = '0';
        return hexStr;
    }
    
    int index = hexSize - 1;
    char* hexCharMap = "0123456789abcdef";
    
    while (uNum > 0) {
        hexStr[index] = hexCharMap[uNum & 15];
        
        uNum >>= 4;
        --index;
    }
    
    return hexStr;
}

int getHexSize(int num) {
    int mask = 16, size = 1;
    
    while ((num & (mask - 1)) != num) {
        mask <<= 4;
        ++size;
    }
    
    return size;
}

/*
 * 409. Longest Palindrome
 * URL: https://leetcode.com/problems/longest-palindrome/
 */
int longestPalindrome(char* s) {
    int len = (int)strlen(s);
    
    if (len == 0)
        return 0;
    
    int* chMapArr = (int*)calloc(58, sizeof(int));
    
    for (int i = 0; i < len; ++i)
        ++chMapArr[s[i] - 'A'];
    
    int result = 0;
    bool isHaveOdd = false;
    
    for (int i = 0; i < 58; ++i) {
        if (i > 25 && i < 32)
            continue;
        
        if (chMapArr[i] % 2 == 0)
            result += chMapArr[i];
        else {
            isHaveOdd = true;
            
            result += (chMapArr[i] - 1);
        }
    }
    
    free(chMapArr);
    
    return result + (isHaveOdd ? 1 : 0);
}

/*
 * 849. Maximize Distance to Closest Person
 * URL: https://leetcode.com/problems/maximize-distance-to-closest-person/
 */
int maxDistance(int dis1, int dis2);
int maxDistToClosest(int* seats, int seatsSize) {
    int maxDist = 0, zeroLens = 0;
    
    for (int i = 0; i < seatsSize; ++i) {
        if (seats[i] == 0)
            ++zeroLens;
        else
            zeroLens = 0;
        
        maxDist = maxDistance(maxDist, (zeroLens + 1) / 2);
    }
    
    // begin with 0, end with 0
    for (int i = 0; i < seatsSize; ++i) {
        if (seats[i] == 1) {
            maxDist = maxDistance(maxDist, i);
            
            break;
        }
    }
    for (int i = seatsSize - 1; i >= 0; --i) {
        if (seats[i] == 1) {
            maxDist = maxDistance(maxDist, seatsSize - i - 1);
            
            break;
        }
    }
    
    return maxDist;
}

int maxDistance(int dis1, int dis2) {
    return dis1 > dis2 ? dis1 : dis2;
}

int minDistance(int dis1, int dis2) {
    return dis1 > dis2 ? dis2 : dis1;
}

int maxDistToClosest2(int* seats, int seatsSize) {
    if (seatsSize == 0)
        return 0;
    
    int* leftCountArr = (int*)malloc(seatsSize * sizeof(int));
    int* rightCountArr = (int*)malloc(seatsSize * sizeof(int));
    
    // initialize
    for (int i = 0; i < seatsSize; ++i) {
        leftCountArr[i] = seatsSize;
        rightCountArr[i] = seatsSize;
    }
    
    // left and right arr
    for (int i = 0; i < seatsSize; ++i) {
        if (seats[i] == 1) {
            leftCountArr[i] = 0;
        } else {
            if (i > 0) {
                leftCountArr[i] = leftCountArr[i - 1] + 1;
            }
        }
    }
    
    for (int i = seatsSize - 1; i >= 0; --i) {
        if (seats[i] == 1) {
            rightCountArr[i] = 0;
        } else {
            if (i < seatsSize - 1) {
                rightCountArr[i] = rightCountArr[i + 1] + 1;
            }
        }
    }
    
    int maxDis = 0;
    for (int i = 0; i < seatsSize; ++i) {
        if (seats[i] == 0) {
            maxDis = maxDistance(maxDis,
                                 minDistance(leftCountArr[i], rightCountArr[i]));
        }
    }
    
    free(leftCountArr);
    free(rightCountArr);
    
    return maxDis;
}

/*
 * 412. Fizz Buzz
 * URL: https://leetcode.com/problems/fizz-buzz/
 */
char** fizzBuzz(int n, int* returnSize) {
    if (n == 0) {
        (*returnSize) = 0;
        
        return NULL;
    }
    
    char** returnArr = (char**)malloc(n * sizeof(char*));
    (*returnSize) = n;
    
    for (int i = 1; i <= (*returnSize); ++i) {
        char* itemStr = NULL;
        if (i % 3 == 0 || i % 5 == 0) {
            if (i % 3 == 0 && i % 5 == 0) {
                itemStr = (char*)calloc(9, sizeof(char));
                
                itemStr = "FizzBuzz";
            } else {
                itemStr = (char*)calloc(5, sizeof(char));
                
                if (i % 3 == 0)
                    itemStr = "Fizz";
                else
                    itemStr = "Buzz";
            }
        } else {
            int len = 1, tmpTen = 10;
            
            while (i / tmpTen) {
                tmpTen *= 10;
                ++len;
            }
            
            itemStr = (char*)calloc(len + 1, sizeof(char));
            int num = i;
            
            do {
                itemStr[len - 1] = num % 10 + 48;
                num /= 10;
                --len;
            } while (num != 0);
        }
        
        returnArr[i - 1] = itemStr;
    }
    
    return returnArr;
}

/*
 * 414. Third Maximum Number
 * URL: https://leetcode.com/problems/third-maximum-number/
 */
int thirdMax(int* nums, int numsSize) {
    long first = LONG_MIN, second = LONG_MIN, third = LONG_MIN;
    
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] >= first) {
            if (nums[i] != first) {
                third = second;
                second = first;
                first = nums[i];
            }
        } else if (nums[i] >= second) {
            if (nums[i] != second) {
                third = second;
                second = nums[i];
            }
        } else if (nums[i] >= third) {
            if (nums[i] != third) {
                third = nums[i];
            }
        }
    }
    
    return (int)(third > LONG_MIN ? third : first);
}

/*
 * 434. Number of Segments in a String
 * URL: https://leetcode.com/problems/number-of-segments-in-a-string/
 */
int countSegments(char* s) {
    if (!s)
        return 0;
    
    int sLen = (int)strlen(s);
    
    if (sLen == 0)
        return 0;
    
    int segment = 0;
    bool isSegment = false;
    
    for (int i = 0; i < sLen; ++i) {
        if (s[i] != ' ') {
            if (!isSegment)
                ++segment;
            
            isSegment = true;
        } else {
            isSegment = false;
        }
    }
    
    return segment;
}

/*
 * 437. Path Sum III
 * URL: https://leetcode.com/problems/path-sum-iii/
 */
void allPathSum(struct TreeNode* root, int sum, int* pathArr, int level,
                int* count);
int pathSum(struct TreeNode* root, int sum) {
    int count = 0;
    
    allPathSum(root, sum, NULL, 1, &count);
    
    return count;
}

void allPathSum(struct TreeNode* root, int sum, int* pathArr, int level,
                int* count) {
    if (!root)
        return ;
    
    int* newPathArr = (int*)malloc(level * sizeof(int));
    int i = 0;
    
    for (i = 0; i < level - 1; ++i)
        newPathArr[i] = pathArr[i] + root->val;
    
    newPathArr[i] = root->val;
    
    for (i = 0; i < level; ++i) {
        if (newPathArr[i] == sum)
            (*count) += 1;
    }
    
    allPathSum(root->left, sum, newPathArr, level + 1, count);
    allPathSum(root->right, sum, newPathArr, level + 1, count);
    
    free(newPathArr);
}

/*
 * 438. Find All Anagrams in a String
 * URL: https://leetcode.com/problems/find-all-anagrams-in-a-string/
 */
bool is2HashEqual(int* sHash, int* pHash);
int* findAnagrams(char* s, char* p, int* returnSize) {
    if (!s || !p)
        return NULL;
    
    int sLen = (int)strlen(s), pLen = (int)strlen(p);
    if (sLen < pLen)
        return NULL;
    
    int* pHash = (int*)calloc(26, sizeof(int));
    int* sHash = (int*)calloc(26, sizeof(int));
    
    int* returnArr = (int*)calloc(sLen, sizeof(int));
    (*returnSize) = 0;
    
    for (int i = 0; i < pLen; ++i) {
        ++pHash[p[i] - 'a'];
        ++sHash[s[i] - 'a'];
    }
    
    for (int i = 0; i <= sLen - pLen; ++i) {
        if (i != 0) {
            ++sHash[s[i + pLen - 1] - 'a'];
        }
        
        if (is2HashEqual(sHash, pHash)) {
            returnArr[(*returnSize)++] = i;
        }
        
        --sHash[s[i] - 'a'];
    }
    
    free(pHash);
    free(sHash);
    
    return returnArr;
}

bool is2HashEqual(int* sHash, int* pHash) {
    for (int i = 0; i < 26; ++i) {
        if (sHash[i] != pHash[i])
            return false;
    }
    
    return true;
}

/*
 * 441. Arranging Coins
 * URL: https://leetcode.com/problems/arranging-coins/
 */
int arrangeCoins(int n) {
    return sqrt(2 * (double)n + 0.25) - 0.5;
}

/*
 * 443. String Compression
 * URL: https://leetcode.com/problems/string-compression/
 */
int compress(char* chars, int charsSize) {
    char* digits = (char*)calloc(200, sizeof(char));
    int totalCount = 0, currentCount = 0;
    
    for (int i = 0; i < charsSize; ++i) {
        ++currentCount;
        
        if (i == charsSize - 1 || chars[i + 1] != chars[i]) {
            chars[totalCount] = chars[i];
            
            if (currentCount > 1) {
                // digit
                int digit = -1;
                
                while (currentCount != 0) {
                    digits[++digit] = currentCount % 10 + '0';
                    currentCount /= 10;
                }
                
                for (int j = digit; j >= 0; --j)
                    chars[++totalCount] = digits[j];
            }
            
            // add the character count
            ++totalCount;
            currentCount = 0;
        }
    }
    
    free(digits);
    
    return totalCount;
}

/*
 * 447. Number of Boomerangs
 * URL: https://leetcode.com/problems/number-of-boomerangs/
 */
#define HASHMAP_SIZE        500

typedef struct DistanceHashMap
{
    int count;
    int distance;
    struct DistanceHashMap* next;
} DisHashMap;

void add2HashMap(DisHashMap* disHashMap, int distance) {
    int slot = distance % HASHMAP_SIZE;
    
    if (disHashMap[slot].distance == distance) {
        ++disHashMap[slot].count;
    } else if (disHashMap[slot].distance == 0) {
        disHashMap[slot].distance = distance;
        
        ++disHashMap[slot].count;
    } else {
        DisHashMap* p = &disHashMap[slot];
        
        while (p->distance != distance && p->next)
            p = p->next;
        
        if (p->distance == distance) {
            ++p->count;
        } else {
            p->next = (DisHashMap*)calloc(1, sizeof(DisHashMap));
            
            p = p->next;
            p->count = 1;
            p->distance = distance;
            p->next = NULL;
        }
    }
}

int cal2PointDistance(int* p1, int* p2) {
    int xDiffAbs = abs(p1[0] - p2[0]);
    int yDiffAbs = abs(p1[1] - p2[1]);
    
    return xDiffAbs * xDiffAbs + yDiffAbs * yDiffAbs;
}

int numberOfBoomerangs(int** points, int pointsRowSize, int pointsColSize) {
    if (!points || pointsRowSize == 0 || pointsColSize == 0)
        return 0;
    
    int totalBoomerangs = 0;
    DisHashMap* disHashMap = (DisHashMap*)calloc(HASHMAP_SIZE,
                                                 sizeof(DisHashMap));
    
    for (int i = 0; i < pointsRowSize; ++i) {
        // clear disHashMap
        for (int j = 0; j < HASHMAP_SIZE; ++j) {
            DisHashMap* curHashMap = &disHashMap[j];
            
            if (curHashMap->next) {
                DisHashMap* p = curHashMap->next;
                
                while (p) {
                    DisHashMap* q = p->next;
                    
                    free(p);
                    p = q;
                }
            }
            
            curHashMap->next = NULL;
            curHashMap->count = 0;
            curHashMap->distance = 0;
        }
        
        // construct distance hashmap
        for (int j = 0; j < pointsRowSize; ++j) {
            if (i == j)
                continue;
            
            add2HashMap(disHashMap, cal2PointDistance(points[i], points[j]));
        }
        
        for (int j = 0; j < HASHMAP_SIZE; ++j) {
            DisHashMap* curHashMap = &disHashMap[j];
            
            while (curHashMap) {
                if (curHashMap->count > 1) {
                    totalBoomerangs += (curHashMap->count *
                                        (curHashMap->count - 1));
                }
                
                curHashMap = curHashMap->next;
            }
        }
    }
    
    // free hashmap
    for (int i = 0; i < HASHMAP_SIZE; ++i) {
        DisHashMap* curHashMap = (&disHashMap[i])->next;
        
        while (curHashMap) {
            DisHashMap* p = curHashMap;

            curHashMap = curHashMap->next;
            free(p);
        }
    }
    
    free(disHashMap);
    
    return totalBoomerangs;
}

/*
 * 448. Find All Numbers Disappeared in an Array
 * URL: https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
 */
int* findDisappearedNumbers(int* nums, int numsSize, int* returnSize) {
    int* numsCountArr = (int*)calloc(numsSize + 1, sizeof(int));
    
    for (int i = 0; i < numsSize; ++i)
        ++numsCountArr[nums[i]];
    
    numsCountArr[0] = 1;
    
    for (int i = 1; i <= numsSize; ++i) {
        if (numsCountArr[i] == 0) {
            numsCountArr[numsCountArr[0]] = i;
            ++numsCountArr[0];
        }
    }
    
    (* returnSize) = numsCountArr[0] - 1;
    
    return &numsCountArr[1];
}

/*
 * 453. Minimum Moves to Equal Array Elements
 * URL: https://leetcode.com/problems/minimum-moves-to-equal-array-elements/
 */
int minMoves(int* nums, int numsSize) {
    if (!nums || numsSize == 0)
        return 0;
    
    int lowest = nums[0], index = 0;
    
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] < lowest) {
            lowest = nums[i];
            
            index = i;
        }
    }
    
    int step = 0;
    
    for (int i = 0; i < numsSize; ++i) {
        if (i != index)
            step += (nums[i] - lowest);
    }
    
    
    return step;
}

int minMoves2(int* nums, int numsSize) {
    if (!nums || numsSize == 0)
        return 0;
    
    long long sum = 0;
    long long lowest = nums[0];
    
    for (int i = 0; i < numsSize; ++i) {
        sum += nums[i];
        
        if (nums[i] < lowest)
            lowest = nums[i];
    }
    
    return (int)(sum - lowest * numsSize);
}

/*
 * 455. Assign Cookies
 * URL: https://leetcode.com/problems/assign-cookies/
 */
int findContentChildren(int* g, int gSize, int* s, int sSize) {
    qsort(g, gSize, sizeof(int), comp);
    qsort(s, sSize, sizeof(int), comp);
    
    int count = 0, j = 0;
    
    for (int i = 0; i < sSize; ++i) {
        if (s[i] > g[j]) {
            ++count;
            ++j;
            
            if (j >= gSize)
                break;
        }
    }
    
    return count;
}

/*
 * 459. Repeated Substring Pattern
 * URL: https://leetcode.com/problems/repeated-substring-pattern/
 */
bool repeatedSubstringPattern(char* s) {
    int len = (int)strlen(s);
    int next[len + 1], j = 0, k = -1;
    
    next[0] = -1;
    
    while (j < len) {
        if (k == -1 || s[j] == s[k])
            next[++j] = ++k;
        else
            k = next[k];
    }
    
    return next[len] && next[len] % (len - next[len]) == 0;
}

/*
 * 461. Hamming Distance
 * URL: https://leetcode.com/problems/hamming-distance/
 */
int hammingDistance(int x, int y) {
    int result = x ^ y;
    int distance = 0;
    
    for (int i = 0; i < 32; ++i) {
        if (result & 1)
            ++distance;
        
        result >>= 1;
    }
    
    return distance;
}

/*
 * 463. Island Perimeter
 * URL: https://leetcode.com/problems/island-perimeter/
 */
int islandPerimeter(int** grid, int gridRowSize, int gridColSize) {
    if (!grid || gridRowSize == 0 || gridColSize == 0)
        return 0;
    
    int oneCount = 0, ajaceCount = 0;
    for (int i= 0; i < gridRowSize; ++i) {
        for (int j = 0; j < gridColSize; ++j) {
            if (grid[i][j] == 1) {
                ++oneCount;
                
                // right side
                if (j < gridColSize - 1 && grid[i][j + 1] == 1) {
                    ++ajaceCount;
                }
                // down side
                if (i < gridRowSize - 1 && grid[i + 1][j] == 1) {
                    ++ajaceCount;
                }
            }
        }
    }
    
    return oneCount * 4 - ajaceCount * 2;
}

/*
 * 475. Heaters
 * URL: https://leetcode.com/problems/heaters/
 */
int compLower(const void* a, const void* b) {
    return *((int*)a) - *((int*)b);
}

int calcMax(int a, int b) {
    return a > b ? a : b;
}

int findRadius(int* houses, int housesSize, int* heaters, int heatersSize){
    qsort(houses, housesSize, sizeof(int), compLower);
    qsort(heaters, heatersSize, sizeof(int), compLower);
    
    int minRadius = 0, j = 0;
    
    for (int i = 0; i < housesSize; ++i) {
        while ((j < heatersSize - 1) && (abs(heaters[j] - houses[i]) >=
                                         abs(heaters[j + 1] - houses[i]))) {
            ++j;        // Find the nearest heater
        }
        
        minRadius = calcMax(minRadius, abs(heaters[j] - houses[i]));
    }
    
    return minRadius;
}

/*
 * 476. Number Complement
 * URL: https://leetcode.com/problems/number-complement/
 */
int findComplement(int num){
    if (num == 0) {
        return 1;
    }
    
    int loc = 0, complementNum = 0;
    
    while (num != 0) {
        int res = num & 1;
        
        complementNum += pow(2, loc++) * (res == 0 ? 1 : 0);
        
        num >>= 1;
    }
    
    return complementNum;
}

/*
 * 482. License Key Formatting
 * URL: https://leetcode.com/problems/license-key-formatting/
 */
char toUpperChar(char ch);
int keyLength(char* s);

char * licenseKeyFormatting(char * S, int K){
    int totalLen = keyLength(S);
    int firstGroupLen = totalLen % K;
    
    // indicate characters length can be divided by K with no remainder
    if (firstGroupLen == 0)
        firstGroupLen = K;
    
    // add dashes and get length
    // add (K - 1) length group to gather the first group
    // if the first group can divided by K without remainder, so add this group
    // is meaningless, else add the group in order to add one dashes in the result
    totalLen += (totalLen + (K - 1)) / K - 1;
    
    if (totalLen < 0)
        totalLen = 0;
    
    char* formatKey = (char*)malloc((totalLen + 1) * sizeof(char));
    
    formatKey[totalLen] = '\0';
    
    // i is the loop of the formatKey array
    // j is the loop of K
    // dashIndex is to find dash position, initialize as K + 1 - firstGroupLen
    // to make the D-value for the first group. It will be set to 1 after find
    // the first place of dash.
    int i = 0, j = 0, dashIndex = K + 1 - firstGroupLen;
    
    while (i < totalLen) {
        if (dashIndex == K + 1) {
            formatKey[i++] = '-';
            
            dashIndex = 1;
        } else {
            // if S[j] is equal to '-', then jump to next,
            // else upper S[j] and set to formatKey[i]
            if (S[j] != '-') {
                formatKey[i++] = toUpperChar(S[j]);
                ++dashIndex;
            }
            
            ++j;
        }
    }
    
    return formatKey;
}

int keyLength(char* s) {
    int len = 0;
    
    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] != '-')
            ++len;
    }
    
    return len;
}

char toUpperChar(char ch) {
    if (ch >= 'a' && ch <= 'z')
        ch -= ('a' - 'A');
    
    return ch;
}

/*
 * 485. Max Consecutive Ones
 * URL: https://leetcode.com/problems/max-consecutive-ones/
 */
int findMaxConsecutiveOnes(int* nums, int numsSize){
    int maxOneNum = 0, oneNum = 0;
    
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] == 0) {
            maxOneNum = maxOneNum < oneNum ? oneNum : maxOneNum;
            
            oneNum = 0;
        } else
            ++oneNum;
    }
    
    maxOneNum = maxOneNum < oneNum ? oneNum : maxOneNum;
    
    return maxOneNum;
}

/*
 * 492. Construct the Rectangle
 * URL: https://leetcode.com/problems/max-consecutive-ones/
 */
int* constructRectangle(int area, int* returnSize){
    int W = sqrt(area);
    
    while (area % W)
        --W;
    
    int* result = (int*)malloc(2 * sizeof(int));
    
    result[0] = area / W;
    result[1] = W;
    
    *returnSize = 2;
    
    return result;
}

/*
 * 496. Next Greater Element I
 * URL: https://leetcode.com/problems/next-greater-element-i/
 */
int* nextGreaterElement(int* nums1, int nums1Size, int* nums2,
                        int nums2Size, int* returnSize){
    if (nums1 == NULL || nums1Size == 0 || nums2 == NULL || nums2Size == 0) {
        (*returnSize) = 0;
        
        return NULL;
    }
    
    (*returnSize) = nums1Size;
    
    // find the max of nums2
    int maxNum = -1;
    
    for (int i = 0; i < nums2Size; ++i) {
        if (maxNum < nums2[i])
            maxNum = nums2[i];
    }
    
    // construct the hash
    int* hashNumArr = (int*)malloc((maxNum + 1) * sizeof(int));
    
    for (int i = 0; i < nums2Size - 1; ++i) {
        hashNumArr[nums2[i]] = -1;
        
        for (int j = i; j < nums2Size; ++j) {
            if (nums2[j] > nums2[i]) {
                hashNumArr[nums2[i]] = nums2[j];
                
                break;
            }
        }
    }
    
    hashNumArr[nums2[nums2Size - 1]] = -1;
    
    int* returnArr = (int*)malloc((*returnSize) * sizeof(int));
    
    for (int i = 0; i < (*returnSize); ++i) {
        returnArr[i] = hashNumArr[nums1[i]];
    }
    
    return returnArr;
}

/*
 * 500. Keyboard Row
 * URL: https://leetcode.com/problems/keyboard-row/
 */
char upper2LowerCase(char ch);
char ** findWords(char ** words, int wordsSize, int* returnSize){
    char* keyboardPosStr = "23321222122233111121131313";
    
    char** resultStrArr = (char**)malloc(sizeof(char*) * wordsSize);
    
    int len = -1;
    for (int i = 0; i < wordsSize; ++i) {
        char* currentStr = words[i];
        char lastPos = keyboardPosStr[upper2LowerCase(currentStr[0]) - 'a'];
        bool tmpRes = true;
        
        for (int j = 1; j < strlen(currentStr); ++j) {
            if (keyboardPosStr[upper2LowerCase(currentStr[j]) - 'a'] != lastPos) {
                tmpRes = false;
                
                break;
            }
        }
        
        if (tmpRes) {
            char* tmpRes = (char*)malloc(sizeof(char) * (strlen(currentStr) + 1));
            tmpRes[strlen(currentStr)] = '\0';
            
            memcpy(tmpRes, currentStr, strlen(currentStr));
            
            ++len;
            resultStrArr[len] = tmpRes;
        }
    }
    
    (* returnSize) = len + 1;
    
    return resultStrArr;
}

char upper2LowerCase(char ch) {
    if (ch >= 'A' && ch <= 'Z')
        ch += ('a' - 'A');
    
    return ch;
}

/*
 * 501. Find Mode in Binary Search Tree
 * URL: https://leetcode.com/problems/find-mode-in-binary-search-tree/
 */
void preTraverse2GetVal(struct TreeNode* root, int** arr, int* len) {
    if (!root)
        return ;
    
    preTraverse2GetVal(root->left, arr, len);
    
    (* arr) = (int*)realloc((* arr), (*len + 1) * sizeof(int));
    (* arr)[*len] = root->val;
    
    (*len) += 1;
    
    preTraverse2GetVal(root->right, arr, len);
}

int* findMode(struct TreeNode* root, int* returnSize){
    int* preTraverseArr = (int*)calloc(0, sizeof(int));
    int len = 0;
    
    preTraverse2GetVal(root, &preTraverseArr, &len);
    
    int* returnArr = (int*)calloc(0, sizeof(int));
    int maxCount = 0;
    int i = 0, j = 0;
    
    for (i = 0; i < len;) {
        for (j = i + 1; j < len; ++j) {
            if (preTraverseArr[j] != preTraverseArr[i])
                break;
        }
        
        int tmpCount = j - i;
        
        if (tmpCount == maxCount) {
            returnArr = (int*)realloc(returnArr, (*returnSize + 1) * sizeof(int));
            returnArr[*returnSize] = preTraverseArr[i];
            
            (*returnSize) += 1;
        } else if (tmpCount > maxCount) {
            if (returnArr)
                free(returnArr);
            
            maxCount = tmpCount;
            (*returnSize) = 1;
            
            returnArr = (int*)calloc(1, sizeof(int));
            returnArr[0] = preTraverseArr[i];
        }
        
        i = j;
    }
    
    return returnArr;
}

/*
 * 504. Base 7
 * URL: https://leetcode.com/problems/base-7/
 */
char * convertToBase7(int num){
    long answer = 0;
    int base = 1;
    
    while (num != 0) {
        answer += (num % 7 * base);
        
        num /= 7;
        base *= 10;
    }
    
    char* str;
    asprintf(&str, "%ld", answer);
    
    return str;
}



int main(int argc, char* argv[]) {
    int nums1[3] = {4, 1, 2};
    int nums2[4] = {1, 3, 4, 2};
    int returnSize = 0;
    
    int* result = nextGreaterElement(nums1, 3, nums2, 4, &returnSize);
    
    free(result);
    
    return 0;
}
