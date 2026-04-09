#include "integrator.hpp"
#include "particle.hpp"
#include <gtest/gtest.h>

constexpr double square(double r) { return r * r; }

TEST(Logic, LeapfrogBasic) {
  using namespace fnb;
  ParticleStore sim;

  Vec3 correct_pos{149597870, 0, 0};
  sim.add_particles({
          {.pos = {0, 0, 0}, .vel = {0, 0, 0}, .mu = 1.327e11, .id = 0}, 
          {.pos = correct_pos, .vel = {0, 29.78, 0}, .mu = 398600, .id = 1},
          {.pos = {228000000., 0, 0}, .vel = {0, 24.1, 0}, .mu = 39860, .id = 2}});

  Leapfrog integ;
  constexpr double step_size = 365. * 86400. / 40.;
  for (int k = 0; k < 40; ++k) {
    integ.step(sim, step_size);
  }

  ASSERT_LE(sim[1].pos().dist2(correct_pos), square(1e7));
}
