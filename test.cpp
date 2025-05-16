#include <iostream>
#include <cstring>

#include "Vonat.hpp"
#include "Jegy.hpp"
#include "dyn_array.hpp"
#include "gtest_lite.h"


int main() {
    
    TEST (jegy, operatorok) {
        Jegy a;
        Jegy b;
        EXPECT_EQ(true, a == b);
        EXPECT_EQ(false, a != b);

        Jegy c(nullptr, 402, "", 2654);
        Jegy d(nullptr, 23, "023", 150);
        EXPECT_EQ(true, c > d);
        EXPECT_EQ(false, c < d);
    } ENDM

    TEST (jegy, elem_eleres) {
        Vonat* v = new Vonat();
        Jegy a(v, 4, "test");

        EXPECT_EQ(0, std::strcmp("test", a["hely"].c_str()));
        EXPECT_EQ("test", a.get<String>("hely").c_str());

        String& ss = a.get<String>("hely");
        ss = String("mas");
        EXPECT_EQ("mas", a.get<String>("hely").c_str());

    } ENDM

    TEST (jegy, kiadas) {
        /*
        Jegy kiadása: 
            stdinről a Jegy mezőit beolvassuk egy interaktív menün keresztül
            A végén "kiadás": stdoutra kiírjuk a Jegy mezőit

            Mindez az elem_eleres tesztesetben bemutatott módon kezeli a Jegy osztályt.
        */
    } ENDM

    TEST (jegy, eladas_osszesites) {
        /*
        stdoutra kiiírjuk az eladott jegyeket tároló dyn_array elemeit
        */
    } ENDM

    TEST (vonat, elem_eleres) {
        Vonat v;

        EXPECT_EQ("0", v["vonatszam"].c_str());
        EXPECT_EQ("0", v.get<String>("vonatszam").c_str());

        int& ss = v.get<int>("vonatszam");
        ss = 2;
        EXPECT_EQ("2", v["vonatszam"].c_str());

    } ENDM

    TEST (vonat, felvetel) {
        Vonat v(1234);
        Vonat vv(4365);
        dyn_array<Vonat> va;
        va.append(v);
        EXPECT_EQ(1, va.occ());
        va.append(vv);
        EXPECT_EQ(2, va.occ());
    } ENDM
    
    TEST (vonat, torol) {
        Vonat v(1234);
        Vonat vv(4365);
        dyn_array<Vonat> va;
        va.append(v);
        va.append(vv);
        EXPECT_EQ(2, va.occ());
        va.arr_delete(1);
        EXPECT_EQ(1, va.occ());
    } ENDM

    TEST (vonat, menetrend_generalas) {
        /*
        stdoutra kiiírjuk az eladott vonatokat tároló dyn_array elemeit
        */
    } ENDM

    TEST (dyn_array_test, hozzaadas) {
        dyn_array<int> da;
        da.append(69);
        EXPECT_EQ(1, da.occ());
        da.append(420);
        EXPECT_EQ(2, da.occ());
    } ENDM

    TEST (dyn_array_test, torles) {
        dyn_array<int> da;
        da.append(69);
        da.append(420);

        EXPECT_EQ(2, da.occ());
        da.arr_delete(1);
        EXPECT_EQ(1, da.occ());
    } ENDM

    TEST (dyn_array_test, elem_eleres) {
        dyn_array<int> da;
        da.append(69);
        da.append(420);

        EXPECT_EQ(69, da[0]);
        EXPECT_EQ(420, da[1]);
        EXPECT_EQ(2, da.occ());
        da.arr_delete(1);
        EXPECT_EQ(1, da.occ());
        da[0] = 123;
        EXPECT_EQ(123, da[0]);
    } ENDM

    return 0;
}