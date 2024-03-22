#ifndef DPP_HPP_
#define DPP_HPP_

#include <qp.hpp>       // QP/C++ real-time embedded framework

//$declare${Shared} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
namespace APP {

//${Shared::AppSignals} ......................................................
enum AppSignals : QP::QSignal {
    EAT_SIG = QP::Q_USER_SIG, // published by Table to let a Philo eat
    DONE_SIG,       // published by Philo when done eating
    PAUSE_SIG,      // published by BSP to pause the application
    SERVE_SIG,      // published by BSP to serve re-start serving forks
    TEST_SIG,       // published by BSP to test the application
    MAX_PUB_SIG,    // the last published signal

    TIMEOUT_SIG,    // posted by time event to Philo
    HUNGRY_SIG,     // posted by hungry Philo to Table
    MAX_SIG         // the last signal
};

//${Shared::produce_sig_dict} ................................................
#ifdef Q_SPY
inline void produce_sig_dict() {
    QS_SIG_DICTIONARY(EAT_SIG,     nullptr);
    QS_SIG_DICTIONARY(DONE_SIG,    nullptr);
    QS_SIG_DICTIONARY(PAUSE_SIG,   nullptr);
    QS_SIG_DICTIONARY(SERVE_SIG,   nullptr);
    QS_SIG_DICTIONARY(TEST_SIG,    nullptr);

    QS_SIG_DICTIONARY(TIMEOUT_SIG, nullptr);
    QS_SIG_DICTIONARY(HUNGRY_SIG,  nullptr);
}
#endif // def Q_SPY

//${Shared::N_PHILO} .........................................................
constexpr std::uint8_t N_PHILO {5};

//${Shared::TableEvt} ........................................................
class TableEvt : public QP::QEvt {
public:
    std::uint8_t philoId;

public:
    constexpr TableEvt(
        QP::QSignal sig,
        std::uint8_t id)
     : QEvt(sig),
       philoId(id)
    {}

#ifdef QEVT_DYN_CTOR
    TableEvt(std::uint8_t id)
      : QEvt(QP::QEvt::DYNAMIC),
        philoId(id)
    {}
#endif // def QEVT_DYN_CTOR
}; // class TableEvt

//${Shared::AO_Philo[N_PHILO]} ...............................................
extern QP::QActive * const AO_Philo[N_PHILO];

//${Shared::AO_Table} ........................................................
extern QP::QActive * const AO_Table;

} // namespace APP
//$enddecl${Shared} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#ifdef QXK_HPP_

namespace APP {

extern QP::QXThread * const TH_XThread1;
extern QP::QXThread * const TH_XThread2;
extern QP::QXSemaphore TH_sema;
extern QP::QXMutex TH_mutex;

} // namespace APP

#endif // QXK_HPP_

#endif // DPP_HPP_
