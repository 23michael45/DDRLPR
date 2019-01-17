#include "Recognizer.h"

namespace DDRLPR{
    void GeneralRecognizer::SegmentBasedSequenceRecognition(PlateInfo &plateinfo){
        for(auto char_instance:plateinfo.plateChars)
        {
            std::pair<CharType,cv::Mat> res;
            if(char_instance.second.rows*char_instance.second.cols>40) {
                label code_table = recognizeCharacter(char_instance.second);
                res.first = char_instance.first;
                code_table.copyTo(res.second);
                plateinfo.appendPlateCoding(res);
            } else{
                res.first = INVALID;
                plateinfo.appendPlateCoding(res);
            }
        }
    }
}