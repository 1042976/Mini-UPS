//
// Created by Xiaodong Liu on 4/16/22.
//

#ifndef FINALPROJECT_SEQNUMCREATOR_H
#define FINALPROJECT_SEQNUMCREATOR_H
#include <stdint.h>
class SeqnumCreator{
private:
    uint64_t uniSeq;
public:
    SeqnumCreator();

    uint64_t updateSeq();

    uint64_t getUniSeq();
};

#endif //FINALPROJECT_SEQNUMCREATOR_H
