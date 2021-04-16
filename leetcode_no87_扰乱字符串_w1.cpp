/* ------------------------------------------------------------------|
使用下面描述的算法可以扰乱字符串 s 得到字符串 t ：
如果字符串的长度为 1 ，算法停止
如果字符串的长度 > 1 ，执行下述步骤：
在一个随机下标处将字符串分割成两个非空的子字符串。即，如果已知字符串 s ，则可以将其分成两个子字符串 x 和 y ，且满足 s = x + y 。
随机 决定是要「交换两个子字符串」还是要「保持这两个子字符串的顺序不变」。即，在执行这一步骤之后，s 可能是 s = x + y 或者 s = y + x 。
在 x 和 y 这两个子字符串上继续从步骤 1 开始递归执行此算法。
给你两个 长度相等 的字符串 s1 和 s2，判断 s2 是否是 s1 的扰乱字符串。如果是，返回 true ；否则，返回 false 。

 

示例 1：

输入：s1 = "great", s2 = "rgeat"
输出：true
解释：s1 上可能发生的一种情形是：
"great" --> "gr/eat" // 在一个随机下标处分割得到两个子字符串
"gr/eat" --> "gr/eat" // 随机决定：「保持这两个子字符串的顺序不变」
"gr/eat" --> "g/r / e/at" // 在子字符串上递归执行此算法。两个子字符串分别在随机下标处进行一轮分割
"g/r / e/at" --> "r/g / e/at" // 随机决定：第一组「交换两个子字符串」，第二组「保持这两个子字符串的顺序不变」
"r/g / e/at" --> "r/g / e/ a/t" // 继续递归执行此算法，将 "at" 分割得到 "a/t"
"r/g / e/ a/t" --> "r/g / e/ a/t" // 随机决定：「保持这两个子字符串的顺序不变」
算法终止，结果字符串和 s2 相同，都是 "rgeat"
这是一种能够扰乱 s1 得到 s2 的情形，可以认为 s2 是 s1 的扰乱字符串，返回 true
示例 2：

输入：s1 = "abcde", s2 = "caebd"
输出：false
示例 3：

输入：s1 = "a", s2 = "a"
输出：true
 

提示：

s1.length == s2.length
1 <= s1.length <= 30
s1 和 s2 由小写英文字母组成

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/scramble-string
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。|
-------------------------------------------------------------------*/

/*	dp记忆优化+递归
*
*	执行用时：28 ms, 在所有 C++ 提交中击败了41.87%的用户
*	内存消耗：17.2 MB, 在所有 C++ 提交中击败了9.70%的用户
*/

#include <iostream>
#include <string> 
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <stack>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}

};

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
    int dp[30][30][31] = { 0 };
    string s1;
    string s2;

    bool check(int i1, int i2, int len) {
        unordered_map<int, int> cnt;
        for (int i = i1; i < i1 + len; ++i) {
            cnt[s1[i]]++;
        }
        for (int i = i2; i < i2 + len; ++i) {
            cnt[s2[i]]--;
        }
        for (auto iter = cnt.begin(); iter != cnt.end(); ++iter) {
            if (iter->second != 0) {
                return false;
            }
        }
        return true;
    }

    bool dfs(int i1,int i2,int len) {
        if (dp[i1][i2][len] == 1) {
            return 1;
        }
        if (dp[i1][i2][len] == -1) {
            return 0;
        }
        if (s1.substr(i1, len) == s2.substr(i2, len)) {
            dp[i1][i2][len] = 1;
            return 1;
        }
        if (!check(i1, i2, len)) {
            dp[i1][i2][len] = -1;
            return 0;
        }
        for (int i = 1; i < len; ++i) {
            if (dfs(i1, i2, i) && dfs(i1 + i, i2 + i, len - i)) {
                dp[i1][i2][len] = 1;
                return 1;
            }
            if (dfs(i1, i2 + len - i, i) && dfs(i1 + i, i2, len - i)) {
                dp[i1][i2][len] = 1;
                return 1;
            }
        }
        dp[i1][i2][len] = -1;
        return 0;
    }

    bool isScramble(string s1, string s2) {
        this->s1 = s1;
        this->s2 = s2;
        return dfs(0, 0, s1.size());
    }
};
