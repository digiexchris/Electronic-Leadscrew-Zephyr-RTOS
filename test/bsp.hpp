//QP/C++ style board support file. Maybe don't need it.
//it contains the startup state of the Active Objects, Queues things like that

#ifndef BSP_HPP_
#define BSP_HPP_

namespace BSP {

constexpr std::uint32_t TICKS_PER_SEC {10000U};

void init();
void start();
void terminate(std::int16_t const result);

} // namespace BSP

#endif // BSP_HPP_

