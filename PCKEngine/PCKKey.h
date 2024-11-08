#ifndef PCKKEY_H
#define PCKKEY_H
class PCKKey {
public:
    int KEY_1 = -1466731422;
    int KEY_2 = -240896429;
    int ASIG_1 = -33685778;
    int ASIG_2 = -267534609;
    int FSIG_1 = 1305093103;
    int FSIG_2 = 1453361591;

    PCKKey() {}

    PCKKey(int key1, int key2)
        : KEY_1(key1), KEY_2(key2) {}

    PCKKey(int key1, int key2, int asig1, int asig2, int fsig1, int fsig2)
        : KEY_1(key1), KEY_2(key2), ASIG_1(asig1), ASIG_2(asig2), FSIG_1(fsig1), FSIG_2(fsig2) {}
};

#endif // PCKKEY_H
