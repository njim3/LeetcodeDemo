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


int main(int argc, char* argv[]) {
    int arr[9] = {1, 1, 1, 2, 2, 3, 4, 5, 5};
    
    struct ListNode* head = createList(arr, 9);
    struct ListNode* res = deleteDuplicates(head);
    
    traverseList(res);
    
    return 0;
}
