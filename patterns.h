#ifndef _PATTERNS_H
#define _PATTERNS_H

typedef const __flash struct {
    const uint8_t l12;
    const uint8_t l34;
    const uint8_t duration;
} pattern_element;

typedef const __flash struct {
    const uint8_t nr_elements;
    const uint8_t rotate;
    const __flash pattern_element * const __flash (*lp_elements)[];
} light_pattern;

const __flash pattern_element lpe_0000_30 = { 0x00, 0x00, 30/5 };
const __flash pattern_element lpe_0000_200 = { 0x00, 0x00, 200/5 };
const __flash pattern_element lpe_0000_400 = { 0x00, 0x00, 400/5 };

const __flash pattern_element lpe_4444_30 = { 0x44, 0x44, 30/5 }; 
const __flash pattern_element lpe_4040_30 = { 0x40, 0x40, 30/5 }; 

const __flash pattern_element lpe_4000_400 = { 0x40, 0x00, 70/5 };
const __flash pattern_element lpe_3100_400 = { 0x31, 0x00, 70/5 };
const __flash pattern_element lpe_2200_400 = { 0x22, 0x00, 70/5 };
const __flash pattern_element lpe_1300_400 = { 0x13, 0x00, 70/5 };

const __flash pattern_element lpe_1000_400 = { 0x10, 0x00, 200/5 };

const __flash pattern_element lpe_1000_5 = { 0x10, 0x00, 1 };
const __flash pattern_element lpe_2000_5 = { 0x20, 0x00, 1 };
const __flash pattern_element lpe_3000_5 = { 0x30, 0x00, 1 };
const __flash pattern_element lpe_4000_5 = { 0x40, 0x00, 1 };


const __flash pattern_element * const __flash lp_elements_dualflash[] = { 
    &lpe_4444_30, &lpe_0000_30, &lpe_4444_30, &lpe_0000_400
};

const __flash pattern_element * const __flash lp_elements_dualflash_split[] = { 
    &lpe_4040_30, &lpe_0000_30, &lpe_4040_30, &lpe_0000_200
};

const __flash pattern_element * const __flash lp_elements_rotate[] = { 
    &lpe_4000_400, &lpe_3100_400, &lpe_2200_400, &lpe_1300_400
};

const __flash pattern_element * const __flash lp_elements_single_dim[] = { 
    &lpe_1000_400
};

const __flash pattern_element * const __flash lp_elements_single_upramp[] = { 
    &lpe_1000_5, &lpe_2000_5, &lpe_3000_5, &lpe_4000_5, &lpe_0000_400
};




const __flash light_pattern lp_dualflash = { 4, 1, &lp_elements_dualflash };
const __flash light_pattern lp_dualflash_s = { 4, 2, &lp_elements_dualflash_split };
const __flash light_pattern lp_rotate = { 4, 4, &lp_elements_rotate };
const __flash light_pattern lp_rotate_dim = { 1, 4, &lp_elements_single_dim };
const __flash light_pattern lp_stand_dim = { 1, 1, &lp_elements_single_dim };
const __flash light_pattern lp_stand_upramp = { 5, 1, &lp_elements_single_upramp };

const __flash light_pattern *light_patterns[] = {
    &lp_stand_upramp,
    &lp_stand_dim,
    &lp_rotate_dim,
    &lp_dualflash,
//    &lp_dualflash_s,
    &lp_rotate
};

#endif //_PATTERNS_H
