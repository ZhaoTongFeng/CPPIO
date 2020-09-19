#pragma once

//����ܻ���ã�ÿ���ַ������̶����ȣ�������д������ַ�����������Ҫ�˷Ѻܶ�ռ䣬���������
//���ǰ��ļ�ѹ����rar����zip֮���ļ�������ֻ������½�������������һ���������
//���Ծ;�����Ҫ�ö����Ƹ�ʽ��������ַ����������ֺ����ַֿ���š�

//��ĳһλ���ó�0����1
void BitSetMask(int& value, int index, bool isT) {
    if (index < 0 || index >= 32) { return; }
    value = isT ? value | (1 << index) : value & (~(1 << index));
    return;
}

//�ж�ĳһλ�Ƿ�Ϊ1
void BitMask(int value, int index, bool& isT) {
    if (index < 0 || index >= 32) { return; }
    isT = ((value >> index) & 1) == 1;
    return;
}