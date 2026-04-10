#include "include/integrator.hpp"
#include "include/particle.hpp"
#include <gtest/gtest.h>

TEST(IntegratorTest, Compensated) {
  using namespace fnb;
  ParticleStore p;
  p.add_particles(
      {{.mu = 1.327e11, .id = 0},
       {.pos{149600000., 0, 0}, .vel{0., 29.78, 0.}, .mu = 398600., .id = 1},
       {.pos{228000000., 0, 0}, .vel{0., 24., 0.}, .mu = 398600., .id = 2}});

  Leapfrog integ;
  integ.gravity = GravityMethod::COMPENSATED;

  for (size_t i = 0; i < 40; ++i) {
    integ.step(p, 365. * 86400. / 40.);
  }

  ASSERT_LE(p[1].pos().dist2({149600000., 0, 0}), 1e14);
}
