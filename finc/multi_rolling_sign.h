#ifndef _MULTI_ROLLING_SIGN_H_
#define _MULTI_ROLLING_SIGN_H_

typedef struct multi_rolling_t multi_rolling_t;

multi_rolling_t *multi_rolling_init(const int columns);
void multi_rolling_sign(multi_rolling_t *mr, int index);

#endif	/* _MULTI_ROLLING_SIGN_H_ */
