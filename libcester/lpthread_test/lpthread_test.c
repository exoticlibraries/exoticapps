//!gcc {0} -I. -lpthread -o out; ./out

#ifndef __BASE_FILE__
#define CESTER_NO_MAIN
#endif
#include <exotic/cester.h>
#include <pthread.h>

CESTER_BODY(

void *show_thread(void* param) {
    for (int i = 0; i < 20; ++i) {
        cester_assert_true(i >= 0);
    }
    return NULL;
}
)

CESTER_TEST(test_thread_one, test_instance,
	int i;
    int rc;
    int count = 4;
    for(int i = 1; i < count; i++ ) 
    {
        pthread_t thread;
        rc = pthread_create(&thread, NULL, show_thread, NULL);
        cester_assert_equal(rc, 0);
        if (rc) {
            printf("cannot create thread \n");
            return;
        }
    }
    //pthread_exit(NULL);
)

#ifndef __BASE_FILE__
CESTER_BODY(
	int main(int argc, char** argv) {
	CESTER_REGISTER_TEST(test1);
	return CESTER_RUN_ALL_TESTS(argc, argv);
}
)
#endif