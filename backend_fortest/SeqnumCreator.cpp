//
// Created on 4/16/22.
//

#include "SeqnumCreator.h"

SeqnumCreator::SeqnumCreator(): uniSeq(0){}

uint64_t SeqnumCreator::updateSeq() {
    std::lock_guard <std::mutex> lck(mtx);
    return ++uniSeq;
}

uint64_t SeqnumCreator::getUniSeq() {
    return uniSeq;
}