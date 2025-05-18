#include <iostream>
#include <cstring>
#include <sstream>

#include "Vonat.hpp"
#include "Jegy.hpp"
#include "dyn_array.hpp"

#include "Menu.h"


#include "gtest_lite.h"

int main() {
#ifdef MEMTRACE
    TEST (Sztring, osszes) {
        // Az ötödik laborfeladaton bemutatott string osztály kód lefedettségéhez
        String s('d');
        String ss1, ss2;
        EXPECT_EQ(1, (int)s.size());
        ss1 = ss2 = s;
        s = s;

        const String konstans("blabla");
        EXPECT_EQ('l', konstans[1]);
        EXPECT_ANY_THROW(konstans[123]);
        std::cout << konstans;
        ss1 = ss1 + String("shesh");
        ss2 = ss2 + 'c';

        char test = 't';
        String g = test + s;

        EXPECT_EQ('s', ss1[1]);
        EXPECT_THROW(ss1[200], const char*);
        String ss3 = ss1 + ss2;
    } ENDM
    
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
        Vonat* v1 = new Vonat(1223);
        Jegy a(v, 4);
        
        a.get<Vonat*>("vonat") = v1;
        a.get<Vonat*>("vonat") = v;
        a.get<int>("kocsiszam")= 301;
        a.get<String>("hely") = String("test");
        a.get<double>("ar") = 0.0;        
        a.get<String>("kedvezmenyek") = String("ingyen_van");
        a.get<int>("kocsiosztaly") = 1;
        a.get<bool>("retur") = true;
        a.get<String>("elado_allomas") = String("BP.Déli");
        EXPECT_ANY_THROW(a.get<char>("vonat"));
        EXPECT_ANY_THROW(a.get<String>("nincsilyen"));
        EXPECT_ANY_THROW(a.get<String>("vonat"));
        EXPECT_ANY_THROW(a.get<char>("lalala"));
        EXPECT_ANY_THROW(a.get<Vonat*>("hihaih"));
        EXPECT_ANY_THROW(a.get<Vonat*>("hely"));
        EXPECT_ANY_THROW(a.get<int>("lalal"));
        EXPECT_ANY_THROW(a.get<int>("kedvezmenyek"));
        EXPECT_ANY_THROW(a.get<double>("valami"));
        EXPECT_ANY_THROW(a.get<double>("kocsiosztaly"));
        EXPECT_ANY_THROW(a.get<bool>("ezmegaz"));
        EXPECT_ANY_THROW(a.get<bool>("vonat"));
             
        
        EXPECT_EQ(0, std::strcmp("0", a["vonat"].c_str()));
        EXPECT_EQ(0, std::strcmp("301", a["kocsiszam"].c_str()));
        EXPECT_EQ(0, std::strcmp("test", a["hely"].c_str()));
        EXPECT_EQ(0, std::strcmp("0.000000", a["ar"].c_str()));
        EXPECT_EQ(0, std::strcmp("ingyen_van", a["kedvezmenyek"].c_str()));
        EXPECT_EQ(0, std::strcmp("1", a["kocsiosztaly"].c_str()));
        EXPECT_EQ(0, std::strcmp("True", a["retur"].c_str()));
        EXPECT_EQ(0, std::strcmp("BP.Déli", a["elado_allomas"].c_str()));
        EXPECT_ANY_THROW(a["nincsilyen"]);

        EXPECT_EQ(0, std::strcmp("test", a.get<String>("hely").c_str()));

        String& ss = a.get<String>("hely");
        ss = String("mas");
        EXPECT_EQ(0, std::strcmp("mas", a.get<String>("hely").c_str()));

        delete v;
        delete v1;

    } ENDM

    TEST (vonat, elem_eleres) {
        Vonat v;

        v.get<int>("vonatszam") = 5536;
        v.get<String>("indulasi_allomas") = "BP.Nyugati";
        v.get<String>("indulasi_ido") = "07:45";
        v.get<String>("erkezesi_allomas") = "Dunakeszi";
        v.get<String>("erkezesi_ido") = "08:03";
        EXPECT_ANY_THROW(v.get<String>("vonatszam"));
        EXPECT_ANY_THROW(v.get<int>("indulasi_ido"));
        EXPECT_ANY_THROW(v.get<int>("ninics"));
        EXPECT_ANY_THROW(v.get<String>("éaelks"));

        EXPECT_EQ(0, std::strcmp("5536", v["vonatszam"].c_str()));
        EXPECT_EQ(0, std::strcmp("BP.Nyugati", v["indulasi_allomas"].c_str()));
        EXPECT_EQ(0, std::strcmp("07:45", v["indulasi_ido"].c_str()));
        EXPECT_EQ(0, std::strcmp("Dunakeszi", v["erkezesi_allomas"].c_str()));
        EXPECT_EQ(0, std::strcmp("08:03", v["erkezesi_ido"].c_str()));
        EXPECT_ANY_THROW(v["nincsilyen"]);
        
        int& ss = v.get<int>("vonatszam");
        ss = 2;
        EXPECT_EQ(0, std::strcmp("2", v["vonatszam"].c_str()));

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

        EXPECT_ANY_THROW(da[100]);
        EXPECT_ANY_THROW(da.arr_delete(203));

        da.append(132);
        da.append(123);
        da.append(731);
        da.append(938);
        da.append(6370);
        da.append(636);
        da.append(643);

        for (int i = 0; i < 6; i++)
            da.arr_delete(0);
        EXPECT_EQ(2, da.occ());
    } ENDM
    
    TEST (Menurendszer, normal) {
        std::stringstream is, os;
        is << "1\nb\nn\nvonatok.txt\n";
        is << "1\nb\ni\nvonatok.txt\n";
        is << "2\nm\nvki.txt\n";
        is << "2\nb\nn\njegyek.txt\n";
        is << "2\nb\ni\njegyek.txt\n";
        is << "2\nm\nki.txt\n";
        is << "3\n1234\nKelenföld\n08:30\nKÖKI\n09:00\n";
        is << "4\n1\n23420\ni\n";
        is << "5\n1234\n402\n101\n1200\nnincs\n2\nFalse\nKÖKI\n";
        is << "6\nn\n";
        is << "7\nn\n";
        is << "8\n";
        Menu m(is, os);
        while (m.active()) {
            EXPECT_NO_THROW(m.nextState());
        }
        
    } ENDM

#endif


#ifndef MEMTRACE
Menu menu;

while (menu.active()) {
    menu.nextState();
}
#endif

    return 0;
}