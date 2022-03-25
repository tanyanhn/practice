#include "catch.hpp"
#include "../lib/config.hpp"
#include "../lib/Vec.h"
#include "../lib/Polynomial.hpp"
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

TEST_CASE("Scalar Polynomial Operations", "[scalar_poly]") {

    using Poly = Polynomial<3, Real>;

    Poly p{1, 2, 1};
    Poly q{2, 5, 4, 1};

    SECTION("Polynomial::==") {
        Poly w{1, 2, 1};
        REQUIRE(p == w);
        REQUIRE_FALSE(q == w);
    }

    SECTION("Polynomial::+") {
        Poly res = p + q;
        Poly ans{3, 7, 5, 1};
        REQUIRE(res == ans);
    }

    SECTION("Polynomial::-") {
        Poly res = p - q;
        Poly ans{-1, -3, -3, -1};
        REQUIRE(res == ans);
    }

    SECTION("Polynomial::*") {
        Poly res = p * q;
        Poly ans{2, 9, 16, 14};
        REQUIRE(res == ans);
    }

    SECTION("Polynomial::eval") {
        Real v = p.eval(3.);
        REQUIRE(v == 16);
    }

    SECTION("Polynomial::derivative") {
        Poly res = q.derivative();
        Poly ans{5, 8, 3};
        REQUIRE(res == ans);
    }

    SECTION("Polynomial::output") {
        ostringstream buf;
        buf << q;
        string res = buf.str();
        string ans{"0[2, 5, 4, 1]3"};
        REQUIRE(res == ans);
    }

    SECTION("Polynomial::coefficient") {
        REQUIRE(q[0] == 2);
        REQUIRE(q[1] == 5);
        REQUIRE(q[2] == 4);
        REQUIRE(q[3] == 1);
    }

}

TEST_CASE("Vector Polynomial Operations", "[vect_poly]") {

    using vec = Vec<3, Real>;
    using Poly = Polynomial<3, vec>;

    Poly p{vec{1, 2, 1}, vec{3, 5, 4}, vec{-2, 1, 0}};
    Poly q{vec{0, 3, 2}, vec{5, -1, -7}, vec{0, 2, 0}, vec{-3, 0, -1}};

    SECTION("Polynomial::==") {
        Poly w{vec{1, 2, 1}, vec{3, 5, 4}, vec{-2, 1, 0}};
        REQUIRE(p == w);
        REQUIRE_FALSE(q == w);
    }

    SECTION("Polynomial::+") {
        Poly res = p + q;
        Poly ans{{1, 5, 3}, {8, 4, -3}, {-2, 3, 0}, {-3, 0, -1}};
        REQUIRE(res == ans);
    }

    SECTION("Polynomial::-") {
        Poly res = p - q;
        Poly ans{{1, -1, -1}, {-2, 6, 11}, {-2, -1, 0}, {3, 0, 1}};
        REQUIRE(res == ans);
    }

    SECTION("Polynomial::*") {
        Poly res = p * q;
        Poly ans{{0, 6, 2}, {5, 13, 1}, {15, 2, -28}, {-13, 9, -1}};
        REQUIRE(res == ans);
    }

    SECTION("Polynomial::/u") {
        Poly res = q / 2.;
        Poly ans{{0, 1.5, 1.}, {2.5, -0.5, -3.5}, {0, 1., 0}, {-1.5, 0, -0.5}};
        REQUIRE(res == ans);
    }

    SECTION("Polynomial::eval") {
        vec v = p.eval(3.);
        REQUIRE(v == vec{-8, 26, 13});
    }

    SECTION("Polynomial::derivative") {
        Poly res = q.derivative();
        Poly ans{{5, -1, -7}, {0, 4, 0}, {-9, 0, -3}};
        REQUIRE(res == ans);
    }

    SECTION("Polynomial::output") {
        ostringstream buf;
        buf << p;
        string res = buf.str();
        string ans{"0[(1,2,1), (3,5,4), (-2,1,0), (0,0,0)]3"};
        REQUIRE(res == ans);
    }

    SECTION("Polynomial::coefficient") {
        REQUIRE(q[0] == vec{0, 3, 2});
        REQUIRE(q[1] == vec{5, -1, -7});
        REQUIRE(q[2] == vec{0, 2, 0});
        REQUIRE(q[3] == vec{-3, 0, -1});
    }

}

