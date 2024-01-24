#include <zephyr/ztest.h>
#include "../../include/Encoder/IEncoder.hpp"
#include <stdint.h>

struct my_suite_fixture {
     size_t max_size;
     size_t size;
     uint8_t buff[1];
};

// static void *encoder_test_setup(void)
// {
//      /* Allocate the fixture with 256 byte buffer */
//    struct my_suite_fixture *fixture = malloc(sizeof(struct my_suite_fixture) + 255);

//      zassume_not_null(fixture, NULL);
//      fixture->max_size = 256;

//      return fixture;
// }

// static void encoder_test_before(void *f)
// {
//      struct my_suite_fixture *fixture = (struct my_suite_fixture *)f;
//      memset(fixture->buff, 0, fixture->max_size);
//      fixture->size = 0;
// }

// static void encoder_test_teardown(void *f)
// {
//    free(f);
// }

// ZTEST_SUITE(encoder_test, NULL, encoder_test_setup, encoder_test_before, NULL, encoder_test_teardown);

ZTEST_SUITE(get_counter_period, NULL, NULL, NULL, NULL, NULL);

class MockEncoder : public Encoder {
     public:
          void Update() override {}

          void SetStatus(Status status) {
               myStatus.store(status);
          }
};

/*
struct Status {
        int32_t count;
        bool direction;
        uint32_t timestamp;
        uint16_t speed;
        uint32_t lastCount;
        bool lastDirection;
        uint32_t lastTimestamp;
        uint16_t lastSpeed;
    };
*/

ZTEST_F(get_counter_period, spindle_stopped)
{
     MockEncoder encoder;
     encoder.SetStatus({0, false, 0, 0, 0, false, 0, 0});

     uint16_t period = encoder.GetCountPeriod();

     zassert_equal(0, period);
     //zassert_equal(256, fixture->max_size);
}

ZTEST_F(get_counter_period, 100ms_per_count_over_10_counts)
{
     Encoder::Status status = {0, false, 1000, 0, 0, false, 0, 0};
     status.count = 10;
     status.lastCount = 0;
     status.timestamp = 2000;
     status.lastTimestamp = 1000;

     MockEncoder encoder;
     encoder.SetStatus(status);

     uint16_t period = encoder.GetCountPeriod();

     zassert_equal(100, period);
}