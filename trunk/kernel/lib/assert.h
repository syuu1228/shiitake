#ifndef LIB_ASSERT_H_
#define LIB_ASSERT_H_

#define assert(expr)						\
	if(!(expr)) {						\
		printf("assert failed at %s:%s:%d\n",		\
		       __FILE__, __FUNCTION__, __LINE__);	\
		while(1)					\
			;					\
	}

#endif
