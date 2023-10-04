#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Sinus.hpp"

TEST_CASE("0 - Project architecture"){
    std::cout << "Project Architecture is OK\n";
}

TEST_CASE("Testing the sinus class"){
    Sinus SinTest;
    CHECK(SinTest.getA0() == doctest::Approx(defaultA0));
    CHECK(SinTest.getAmplitude() == doctest::Approx(defaultAmplitude));
    CHECK(SinTest.getOmega() == doctest::Approx(defaultOmega));
    CHECK(SinTest.getPhi0() == doctest::Approx(defaultPhi0));

    CHECK(SinTest.gettstart() == doctest::Approx(defaultStart));
    CHECK(SinTest.gettstop() == doctest::Approx(defaultStop));
    CHECK(SinTest.getNbPoints() == defaultNbPoints);
};


TEST_CASE("Testing the sinus class with parameter") {
    Sinus SinTest;
    float A0 = 2.2;
    SinTest.setA0(A0);
    CHECK(SinTest.getA0() == doctest::Approx(A0));

    float amp = 3.3;
    SinTest.setAmplitude(amp);
    CHECK(SinTest.getAmplitude() == doctest::Approx(amp));

    float pi = std::numbers::pi;
    float OMG = 2*pi;
    SinTest.setOmega(OMG);
    CHECK(SinTest.getOmega() == doctest::Approx(OMG));

    OMG = -OMG;		// check omega pas negatif
    CHECK_THROWS_WITH_AS(SinTest.setOmega(OMG), "Omega can’t be negative.", std::domain_error);

    float 	Phi0 = pi / 4;
    SinTest.setPhi0(Phi0);
    CHECK(SinTest.getPhi0() == doctest::Approx(Phi0));

    SinTest.setPhi0(Phi0 + 2*pi);
    CHECK(SinTest.getPhi0() == doctest::Approx(Phi0));


    SinTest.setPhi0(Phi0 + 3*pi);
    CHECK(SinTest.getPhi0() == doctest::Approx(-Phi0));
};

