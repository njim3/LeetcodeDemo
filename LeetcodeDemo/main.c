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
struct ListNode {
    int val;
    struct ListNode* next;
};

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
 * URL: https://leetcode.com/problems/maximum-subarray/
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


int main(int argc, char* argv[]) {
    char* s = "       aaaa    ";
    
    printf("%d\n", lengthOfLastWord(s));
    
    
    return 0;
}
