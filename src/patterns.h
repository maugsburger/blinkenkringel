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
const __flash pattern_element lpe_0000_50 = { 0x00, 0x00, 50/5 };
const __flash pattern_element lpe_0000_200 = { 0x00, 0x00, 200/5 };
const __flash pattern_element lpe_0000_400 = { 0x00, 0x00, 400/5 };

const __flash pattern_element lpe_4444_30 = { 0x44, 0x44, 30/5 }; 
const __flash pattern_element lpe_4444_50 = { 0x44, 0x44, 50/5 }; 
const __flash pattern_element lpe_4040_30 = { 0x40, 0x40, 30/5 }; 

const __flash pattern_element lpe_4444_100 = { 0x44, 0x44, 100/5 }; 
const __flash pattern_element lpe_3333_100 = { 0x33, 0x33, 100/5 }; 
const __flash pattern_element lpe_2222_100 = { 0x22, 0x22, 100/5 }; 
const __flash pattern_element lpe_1111_100 = { 0x11, 0x11, 100/5 }; 

const __flash pattern_element lpe_4000_70 = { 0x40, 0x00, 70/5 };
const __flash pattern_element lpe_3100_70 = { 0x31, 0x00, 70/5 };
const __flash pattern_element lpe_2200_70 = { 0x22, 0x00, 70/5 };
const __flash pattern_element lpe_1300_70 = { 0x13, 0x00, 70/5 };

const __flash pattern_element lpe_4000_30 = { 0x40, 0x00, 30/5 };
const __flash pattern_element lpe_3100_30 = { 0x31, 0x00, 30/5 };
const __flash pattern_element lpe_2200_30 = { 0x22, 0x00, 30/5 };
const __flash pattern_element lpe_1300_30 = { 0x13, 0x00, 30/5 };

const __flash pattern_element lpe_4000_10 = { 0x40, 0x00, 10/5 };
const __flash pattern_element lpe_3100_10 = { 0x31, 0x00, 10/5 };
const __flash pattern_element lpe_2200_10 = { 0x22, 0x00, 10/5 };
const __flash pattern_element lpe_1100_10 = { 0x13, 0x00, 10/5 };

const __flash pattern_element lpe_1000_400 = { 0x10, 0x00, 200/5 };

const __flash pattern_element lpe_1000_5 = { 0x10, 0x00, 1 };
const __flash pattern_element lpe_2000_5 = { 0x20, 0x00, 1 };
const __flash pattern_element lpe_3000_5 = { 0x30, 0x00, 1 };
const __flash pattern_element lpe_4000_5 = { 0x40, 0x00, 1 };


const __flash pattern_element * const __flash lp_elements_dualflash[] = { 
    &lpe_4444_30, &lpe_0000_30, &lpe_4444_30, &lpe_0000_200
};

const __flash pattern_element * const __flash lp_elements_dualflash_split[] = { 
    &lpe_4040_30, &lpe_0000_30, &lpe_4040_30, &lpe_0000_200
};

const __flash pattern_element * const __flash lp_elements_flash_split[] = { 
    &lpe_4040_30, &lpe_0000_30
};

const __flash pattern_element * const __flash lp_elements_rotate[] = { 
    &lpe_4000_70, &lpe_3100_70, &lpe_2200_70, &lpe_1300_70
};

const __flash pattern_element * const __flash lp_elements_rotate_fast[] = { 
    &lpe_4000_30, &lpe_3100_30, &lpe_2200_30, &lpe_1300_30
};

const __flash pattern_element * const __flash lp_elements_rotate_superfast[] = { 
    &lpe_4000_10, &lpe_3100_10, &lpe_2200_10, &lpe_1100_10
};

const __flash pattern_element * const __flash lp_elements_single_dim[] = { 
    &lpe_1000_400
};

const __flash pattern_element * const __flash lp_elements_flash_dim[] = { 
    &lpe_1111_100, &lpe_0000_400,
};

const __flash pattern_element * const __flash lp_elements_single_upramp[] = { 
    &lpe_1000_5, &lpe_2000_5, &lpe_3000_5, &lpe_4000_5, &lpe_0000_400
};

const __flash pattern_element * const __flash lp_elements_rampall[] = { 
    &lpe_1111_100,
    &lpe_2222_100,
    &lpe_3333_100,
    &lpe_4444_100,
    &lpe_3333_100,
    &lpe_2222_100,
};

const __flash pattern_element * const __flash lp_elements_rampallflash[] = { 
    &lpe_1111_100,
    &lpe_2222_100,
    &lpe_3333_100,
    &lpe_0000_30,
    &lpe_4444_30,
    &lpe_0000_30,
    &lpe_4444_30,
    &lpe_0000_30,
    &lpe_3333_100,
    &lpe_2222_100,
};

const __flash pattern_element * const __flash lp_elements_allmax[] = { 
    &lpe_4444_50
};

const __flash pattern_element * const __flash lp_elements_alldim[] = { 
    &lpe_1111_100,
};


const __flash light_pattern lp_dualflash = { 4, 1, &lp_elements_dualflash };
const __flash light_pattern lp_dualflash_s = { 4, 2, &lp_elements_dualflash_split };
const __flash light_pattern lp_flash_s = { 4, 2, &lp_elements_flash_split };
const __flash light_pattern lp_flash_dim = { 2, 1, &lp_elements_flash_dim };
const __flash light_pattern lp_rotate = { 4, 4, &lp_elements_rotate };
const __flash light_pattern lp_rotate_fast = { 4, 4, &lp_elements_rotate_fast };
const __flash light_pattern lp_rotate_superfast = { 4, 4, &lp_elements_rotate_superfast };
const __flash light_pattern lp_rotate_dim = { 1, 4, &lp_elements_single_dim };
const __flash light_pattern lp_stand_dim = { 1, 1, &lp_elements_single_dim };
const __flash light_pattern lp_stand_upramp = { 5, 1, &lp_elements_single_upramp };
const __flash light_pattern lp_rampall = { 6, 1, &lp_elements_rampall };
const __flash light_pattern lp_rampallflash = { 10, 1, &lp_elements_rampallflash };
const __flash light_pattern lp_all_max = { 1, 1, &lp_elements_allmax };
const __flash light_pattern lp_all_dim = { 1, 1, &lp_elements_alldim };

const __flash light_pattern *light_patterns[] = {
    &lp_rotate,
    &lp_rotate_fast,
    &lp_rotate_superfast,
    &lp_rampall,
    &lp_rampallflash,
    &lp_flash_s,
    &lp_dualflash,
    &lp_dualflash_s,
    &lp_rotate_dim,
    &lp_flash_dim,
    &lp_all_dim,
};

#endif //_PATTERNS_H
