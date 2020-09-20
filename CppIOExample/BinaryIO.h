#pragma once


namespace MBinaryIO {
    //位操作
    //把某一位设置成0或者1
    static void SetBit(int& value, int index, bool isT) {
        if (index < 0 || index >= 32) { return; }
        value = isT ? value | (1 << index) : value & (~(1 << index));
        return;
    }

    //判断某一位是否为1
    static void GetMask(int value, int index, bool& isT) {
        if (index < 0 || index >= 32) { return; }
        isT = ((value >> index) & 1) == 1;
        return;
    }
}
