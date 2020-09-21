#pragma once


namespace MBinFileIO {
    //λ����
    //��ĳһλ���ó�0����1
    void SetBit(int& value, int index, bool isT) {
        if (index < 0 || index >= 32) { return; }
        value = isT ? value | (1 << index) : value & (~(1 << index));
        return;
    }

    //�ж�ĳһλ�Ƿ�Ϊ1
    void GetMask(int value, int index, bool& isT) {
        if (index < 0 || index >= 32) { return; }
        isT = ((value >> index) & 1) == 1;
        return;
    }
}