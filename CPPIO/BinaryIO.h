#pragma once

//你可能会觉得，每个字符串都固定长度，那如果有大量的字符串，那岂不是要浪费很多空间，是这个道理。
//但是把文件压缩成rar或者zip之后，文件的体积又会大幅度下降，我们来进行一个体积测试
//所以就尽量不要用二进制格式保存大量字符串，将文字和数字分开存放。

//把某一位设置成0或者1
void BitSetMask(int& value, int index, bool isT) {
    if (index < 0 || index >= 32) { return; }
    value = isT ? value | (1 << index) : value & (~(1 << index));
    return;
}

//判断某一位是否为1
void BitMask(int value, int index, bool& isT) {
    if (index < 0 || index >= 32) { return; }
    isT = ((value >> index) & 1) == 1;
    return;
}