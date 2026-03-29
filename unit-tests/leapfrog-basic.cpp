#include "integrator.hpp"
#include "particle.hpp"
#include <iostream>
#include <gtest/gtest.h>

TEST(Logic, LeapfrogBasic) {
  using namespace fnb;
  ParticleStore sim;
  ParticleStore dummy;

  Vec3 correct_pos{149597870, 0, 0};
  sim.add_particles({{.mu = 1.327e11, .id = 0, .pos = {0, 0, 0}, .vel = {0, 0, 0}}, {.mu = 398600, .id = 1, .pos = correct_pos, .vel = {29.78, 0, 0}}});
  Leapfrog integ;
  constexpr double step_size = 365 * 86400 / 40;
  for (int k = 0; k < 40; ++k) {
    integ.step(sim, dummy, step_size);
  }

  for (size_t i = 0; i < sim.N(); ++i) std::cout << "Element " << i << " pos: " << sim[i].pos().x  << ' ' << sim[i].pos().y << ' ' << sim[i].pos().z << '\n';

  ASSERT_LE(sim[1].pos().dist2(correct_pos), 1000 * 1000);
}
