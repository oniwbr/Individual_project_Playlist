// Copyright 2025 Kanukova Margarita
#include <iostream>
#include <Windows.h>
#include "/Github/Individual_project_Playlist/Platform/Tvector/tvector.h"


void set_color(int text_color, int bg_color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bg_color << 4) | text_color);
}

namespace TestSystem {
    int count_success = 0, count_failed = 0;

    void start_test(bool(*test)(), const char* name_of_test) {
        set_color(2, 0);
        std::cout << "[ RUN      ] ";
        set_color(7, 0);
        std::cout << name_of_test << std::endl;

        bool status = test();

        if (status == true) {
            set_color(2, 0);
            std::cout << "[       OK ]" << std::endl;
            count_success++;
        }
        else {
            set_color(4, 0);
            std::cout << "[  FAILED  ]" << std::endl;
            count_failed++;
        }
        set_color(7, 0);
    }

    template <class T>
    bool check(const T& expected, const T& actual) {
        if (expected == actual) {
            return true;
        }
        else {
            std::cerr << "Expected result is " << expected << ", but actual is " << actual << "." << std::endl;
            return false;
        }
    }

    void print_init_info() {
        set_color(2, 0);
        std::cout << "[==========] " << std::endl;
        set_color(7, 0);
    }

    void print_final_info() {
        set_color(2, 0);
        std::cout << "[==========] ";
        set_color(7, 0);
        std::cout << count_success + count_failed << " test" << (count_success + count_failed > 1 ? "s" : "") << " ran." << std::endl;
        set_color(2, 0);
        std::cout << "[  PASSED  ] ";
        set_color(7, 0);
        std::cout << count_success << " test" << (count_success > 1 ? "s" : "") << std::endl;
        if (count_failed > 0) {
            set_color(4, 0);
            std::cout << "[  FAILED  ] ";
            set_color(7, 0);
            std::cout << count_failed << " test" << (count_failed > 1 ? "s." : ".") << std::endl;
        }
    }
};

bool test_1_create_default_vec() {
    TVector<int> vec;
    return TestSystem::check((size_t)0, vec.size()) && TestSystem::check((size_t)15, vec.capacity());
}

bool test_2_create_with_size() {
    TVector<int> vec(15);
    return TestSystem::check((size_t)15, vec.size()) && TestSystem::check((size_t)30, vec.capacity());
}

bool test_3_create_with_array_and_size() {
    int mass[4] = { 1,2,3,4 };
    TVector<int> vec(4, mass);
    bool expected = true, actual = true;
    for (size_t i = 0; i < vec.size(); i++) {
        if (vec[i] == mass[i]) actual &= true;
    }
    return TestSystem::check(expected, actual) && TestSystem::check((size_t)4, vec.size()) &&
        TestSystem::check((size_t)15, vec.capacity());
}

bool test_4_create_with_list() {
    int mass[4] = { 1,2,3,4 };
    TVector<int> vec{ 1,2,3,4 };
    bool expected = true, actual = true;
    for (size_t i = 0; i < vec.size(); i++) {
        if (mass[i] == vec[i]) actual &= true;
    }
    return TestSystem::check(expected, actual) && TestSystem::check((size_t)4, vec.size()) &&
        TestSystem::check((size_t)15, vec.capacity());
}

bool test_5_create_with_copying() {
    bool expected = true, actual = true;
    TVector<int> vec1(4, { 1,2,3,4 }), vec2(vec1);
    for (size_t i = 0; i < vec1.size(); i++) {
        if (vec1[i] == vec2[i]) actual &=true;
    }
    return TestSystem::check(expected, actual) && TestSystem::check(vec1.size(), vec2.size()) &&
        TestSystem::check(vec1.capacity(), vec2.capacity());
}

bool test_6_create_with_copying_throw() {
    bool expected = true, actual = false;
    TVector<int>* vec1 = NULL;
    try {
        TVector<int> vec2(*vec1);
    }
    catch (const std::exception& ex) {
        actual = true;
    }
    return TestSystem::check(expected, actual);
}

bool test_7_create_with_size_and_array() {
    bool expected = true, actual = true;
    int mass[3] = { 8,8,8 };
    TVector<int> vec(3, 8);
    for (size_t i = 0; i < vec.size(); i++) {
        if (mass[i] == vec[i]) actual &= true;
    }
    return TestSystem::check(expected, actual) && TestSystem::check((size_t)3, vec.size()) &&
        TestSystem::check((size_t)15, vec.capacity());
}

bool test_8_access_front_elem() {
    int value = 8, mass[4] = { 1,2,3,4 };
    TVector<int> vec{ 1,2,3,4 };

    int first_elem = vec.front();
    vec.front() = value;
    return TestSystem::check(mass[0], first_elem) && TestSystem::check(value, vec.front());
}

bool test_9_access_front_elem_throw() {
    bool expected = true, actual = false;
    TVector<int> vec;

    try {
        int element = vec.front();
    }
    catch (const std::exception& ex) {
        actual = true;
    }
    return TestSystem::check(expected, actual);
}

bool test_10_access_back_elem() {
    int value = 26, mass[4] = { 1,2,3,4 };
    TVector<int> vec{ 1,2,3,4 };

    int last_elem = vec.back();
    vec.back() = value;
    return TestSystem::check(mass[3], last_elem) && TestSystem::check(value, vec.back());
}

bool test_11_access_back_elem_throw() {
    bool expected = true, actual = false;
    TVector<int> vec;
    
    try {
        int elem = vec.back();
    }
    catch (const std::exception& ex) {
        actual = true;
    }
    return TestSystem::check(expected, actual);
}

bool test_12_check_operator_equality_true() {
    bool expected = true, actual = false;
    TVector<int> vec1{ 1,2,3,4 }, vec2{ 1,2,3,4 };
    actual = (vec1 == vec2);
    return TestSystem::check(expected, actual);
}

bool test_13_check_operator_equlity_false() {
    bool expected = false, actual = false;
    TVector<int> vec1{ 1,2 }, vec2{ 1,2,3,4 };

    actual = (vec1 == vec2);

    return TestSystem::check(expected, actual);
}

bool test_14_checl_operator_inequality_true() {
    bool expected = true, actual = true;
    TVector<int> vec1{ 1,2 }, vec2{ 1,2,3,4 };
    
    actual = (vec1 != vec2);
    return TestSystem::check(expected, actual);
}

bool test_15_check_operator_inequality_false() {
    bool expected = false, actual = false;
    TVector<int> vec1{ 1,2,3,4 }, vec2{ 1,2,3,4 };

    actual = (vec1 != vec2);

    return TestSystem::check(expected, actual);
}

bool test_16_check_operator_brackets() {
    int value = 8;
    int mass[4] = { 1, 2, 3, 4 };
    const TVector<int> vec1({ 1, 2, 3, 4 });
    TVector<int> vec2({ 1, 2, 3, 4 });

    vec2[3] = value;

    return TestSystem::check(mass[2], vec1[2]) &&
        TestSystem::check(value, vec2[3]);
}

bool test_17_check_operator_assign() {
    bool expected = true, actual = true;
    TVector<int> vec1{ 1, 2, 3, 4 };
    TVector<int> vec2{ 1, 2, 3 };
    vec1 = vec2;

    actual &= (vec1 == vec2);

    return TestSystem::check(expected, actual) &&
        TestSystem::check(vec2.size(), vec1.size()) &&
        TestSystem::check(vec2.capacity(), vec1.capacity());
}

bool test_18_check_push_front() {
    bool expected = true, actual = true;
    TVector<int> vec1{ 1,2,3,4 }, vec2{ 11,1,2,3,4 };
    vec1.push_front(11);

    actual = (vec1 == vec2);

    return TestSystem::check(expected, actual) && TestSystem::check(vec2.size(), vec1.size()) &&
        TestSystem::check(vec2.capacity(), vec1.capacity());
}

bool test_19_check_push_front_with_reallocation_memory() {
    bool expected = true, actual = true;
    TVector<int> vec1( 13, 8 );
    vec1.push_front(3);
    vec1.push_front(2);
    vec1.push_front(1);

    TVector<int> vec2{ 1,2,3,8,8,8,8,8,8,8,8,8,8,8,8,8 };
    actual = (vec1 == vec2);
    return TestSystem::check(expected, actual) && TestSystem::check(vec2.size(), vec1.size()) &&
        TestSystem::check(vec2.capacity(), vec1.capacity());
}

bool test_20_check_push_back() {
    bool expected = true, actual = true;
    TVector<int> vec1{ 1,2,3 }, vec2{ 1,2,3,26 };
    vec1.push_back(26);

    actual = (vec1 == vec2);

    return TestSystem::check(expected, actual) && TestSystem::check(vec2.size(), vec1.size()) &&
        TestSystem::check(vec2.capacity(), vec1.capacity());
}

bool test_21_check_push_back_with_reallocation_memory() {
    bool expected = true, actual = true;
    TVector<int> vec1(13, 8);
    vec1.push_back(9);
    vec1.push_back(10);
    vec1.push_back(11);

    TVector<int> vec2{ 8,8,8,8,8,8,8,8,8,8,8,8,8,9,10,11 };
    actual = (vec1 == vec2);
    return TestSystem::check(expected, actual) && TestSystem::check(vec2.size(), vec1.size()) &&
        TestSystem::check(vec2.capacity(), vec1.capacity());
}

bool test_22_check_insert() {
    bool expected = true, actual = true;
    TVector<int> vec1{ 1, 2, 3, 4 };

    TVector<int> vec2{ 1, 2, 8, 3, 4 };
    TVector<int> vec3{ 1, 2, 8, 3, 4, 26, 26 };
    TVector<int> vec4{ 1, 2, 8, 3, 4, 26, 24, 23, 11, 26 };

    vec1.insert(2, 8);
    actual &= (vec1 == vec2);
    vec1.insert(5, 2, 26);
    actual &= (vec1 == vec3);
    vec1.insert(6, { 24, 23, 11 });
    actual &= (vec1 == vec4);

    return TestSystem::check(expected, actual);
}

bool test_23_check_insert_with_reallocation_memory() {
    bool expected = true, actual = true;
    TVector<int> vec1(14, 8);
    vec1.insert(1, 7);
    vec1.insert(10, 9);

    TVector<int> vec2{ 8,7,8,8,8,8,8,8,8,8,9,8,8,8,8,8 };
    actual = (vec1 == vec2);
    return TestSystem::check(expected, actual) && TestSystem::check(vec2.size(), vec1.size()) &&
        TestSystem::check(vec2.capacity(), vec1.capacity());
}

bool test_24_try_insert_throw() {
    bool expected = true, actual = false;
    TVector<int> vec{ 1,2,3,4,5 };

    try {
        vec.insert(7, 6);
    }
    catch (const std::exception& ex) {
        actual = true;
    }

    return TestSystem::check(expected, actual);
}

bool test_25_check_pop_front() {
    bool expected = true, actual = true;
    TVector<int> vec1{ 1,2,3,4,5 }, vec2{ 2,3,4,5 };
    vec1.pop_front();

    actual = (vec1 == vec2);

    return TestSystem::check(expected, actual) &&
        TestSystem::check(vec2.size(), vec1.size()) &&
        TestSystem::check(vec2.capacity(), vec1.capacity());
}

bool test_26_try_pop_front_throw() {
    bool expected = true, actual = false;
    TVector<int> vec;

    try {
        vec.pop_front();
    }
    catch (const std::exception& ex) {
        actual = true;
    }

    return TestSystem::check(expected, actual);
}

bool test_27_check_pop_back() {
    bool expected = true, actual = true;
    TVector<int> vec1{ 1,2,3,4 }, vec2{ 1,2,3 };
    vec1.pop_back();
    actual = (vec1 == vec2);

    return TestSystem::check(expected, actual) &&
        TestSystem::check(vec2.size(), vec1.size()) &&
        TestSystem::check(vec2.capacity(), vec1.capacity());
}

bool test_28_check_pop_back_throw() {
    bool expected = true, actual = false;
    TVector<int> vec;

    try {
        vec.pop_back();
    }
    catch (const std::exception& ex) {
        actual = true;
    }

    return TestSystem::check(expected, actual);
}

bool test_29_check_erase() {
    bool expected = true, actual = true;
    TVector<int> vec1{ 1,2,3,4,5 }, vec2{  2, 3, 4, 5 }, vec3{ 2, 5 };
    vec1.erase(0);
    actual &= (vec1 == vec2);
    vec1.erase(1, 2);
    actual &= (vec1==vec3);

    return TestSystem::check(expected, actual);
}

bool test_30_check_erase_throw() {
    bool expected = true, actual = false;
    TVector<int> vec;

    try {
        vec.erase(0);
    }
    catch (const std::exception& ex) {
        actual = true;
    }

    return TestSystem::check(expected, actual);
}

bool test_31_check_replace() {
    bool expected = true, actual = true;
    TVector<int> vec1{ 1, 2, 3, 4, 5 }, vec2{ 1, 2, 7, 4, 5 }, vec3{ 1, 2, 3, 4, 5 };

    vec1.replace(2, 7);
    actual &= (vec1 == vec2);
    vec1.replace(vec1.data() + 2, 3);
    actual &= (vec1 == vec3);

    return TestSystem::check(expected, actual);
}

bool test_32_check_replace_after_deleted() {
    bool expected = true, actual = true;
    TVector<int> vec1(10, 8);
    vec1.erase(2);
    vec1.replace(2, 9);

    TVector<int> vec2{ 8,8,9,8,8,8,8,8,8 };

    actual &= (vec1 == vec2);
    actual &= (*(vec1.data() + 2) != *(vec2.data() + 2));

    return TestSystem::check(expected, actual);
}

bool test_33_check_replace_throw() {
    bool expected = true, actual = false;
    TVector<int> vec{ 1,2,3,4,5 };

    try {
        vec.replace(5, 6);
    }
    catch (const std::exception& ex) {
        actual = true;
    }

    return TestSystem::check(expected, actual);
}

bool test_34_check_replace_ptr_throw() {
    bool expected = true, actual = false;
    TVector<int> vec{ 1, 2, 3, 4, 5 };

    try {
        vec.replace(vec.data() + 5, 6);
    }
    catch (const std::exception& ex) {
        actual = true;
    }

    return TestSystem::check(expected, actual);
}

bool test_35_check_replace_deleted_elem() {
    bool expected = true, actual = false;
    TVector<int> vec(14, 2);
    vec.erase(2);

    try {
        vec.replace(vec.data() + 2, 555);
    }
    catch (const std::exception& ex) {
        actual = true;
    }

    return TestSystem::check(expected, actual);
}

bool test_36_check_assign_with_size_value() {
    bool expected = true, actual = true;
    TVector<int> vec1(16, 1);
    vec1.assign(4, 0);

    TVector<int> vec2{ 0, 0, 0, 0 };

    actual = (vec1 == vec2);

    return TestSystem::check(expected, actual) &&
        TestSystem::check(vec2.size(), vec1.size());
}

bool test_37_check_assign_with_array() {
    bool expected = true, actual = true;
    TVector<int> vec1;
    vec1.assign({ 8,8,8 });

    TVector<int> vec2{8,8,8};

    actual = (vec1 == vec2);

    return TestSystem::check(expected,actual) &&
        TestSystem::check(vec2.size(), vec1.size());
}

bool test_38_check_assgin_with_reallocation_memory() {
    bool expected = true, actual = true;
    TVector<int> vec1, vec3(35, 1);
    vec1.assign(16, 0);
    vec3.assign(16, 0);

    TVector<int> vec2(16, 0);

    actual &= (vec1 == vec2);
    actual &= (vec3 == vec2);
    actual &= (vec2.capacity() != vec3.capacity());

    return TestSystem::check(expected, actual) &&
        TestSystem::check(vec2.size(), vec1.size()) &&
        TestSystem::check(vec2.capacity(), vec1.capacity()) &&
        TestSystem::check(vec2.size(), vec3.size());
}

bool test_39_try_access_to_elem_out_of_range() {
    bool expected = true, actual = false;
    TVector<int> vec(3);

    try {
        int elem = vec.at(3);
    }
    catch (const std::exception& ex) {
        actual = true;
    }

    return TestSystem::check(expected, actual);
}

bool test_40_check_clear() {
    TVector<int> vec{ 1,2,3,4,5,6,7,8,9,10 };

    vec.clear();

    return TestSystem::check((size_t)0, vec.size()) &&
        TestSystem::check((size_t)15, vec.capacity());
}

bool test_41_check_reserve_with_less_cap() {
    TVector<int> vec(16, 1);
    vec.reserve(17);

    return TestSystem::check((size_t)16, vec.size()) &&
        TestSystem::check(size_t(30), vec.capacity());
}

bool test_42_check_reserve_with_bigger_cap() {
    TVector<int> vec(12, 0);
    vec.reserve(17);

    return TestSystem::check(size_t(12), vec.size()) &&
        TestSystem::check(size_t(17), vec.capacity());
}

bool test_43_check_resize_with_less_size() {
    bool expected = true, actual = true;
    TVector<int> vec1(13, 0);
    vec1.resize(9);

    TVector<int> vec2(9, 0);

    actual = (vec1 == vec2);

    return TestSystem::check(expected, actual) &&
        TestSystem::check(vec2.size(), vec1.size()) &&
        TestSystem::check(vec2.capacity(), vec1.capacity());
}

bool test_44_check_resize_with_less_size_cap() {
    bool expected = true, actual = true;
    TVector<int> vec1(18, 9);
    vec1.resize(9);

    TVector<int> vec2(9, 9);

    actual = (vec1 == vec2);

    return TestSystem::check(expected, actual) &&
        TestSystem::check(vec2.size(), vec1.size()) &&
        TestSystem::check(vec2.capacity(), vec1.capacity());
}

bool test_45_check_resize_with_bigger_size() {
    TVector<int> vec1(10, 2);
    vec1.resize(15);

    TVector<int> vec2(15);

    return TestSystem::check(vec2.size(), vec1.size()) &&
        TestSystem::check(vec2.capacity(), vec1.capacity());
}

bool test_46_check_resize_with_bigger_size_cap() {
    TVector<int> vec1(10, 0), vec2(16, 0);
    vec1.resize(16);

    return TestSystem::check(vec2.size(), vec1.size()) &&
        TestSystem::check(vec2.capacity(), vec1.capacity());
}

bool test_47_check_resize_with_value() {
    bool expected = true, actual = true;
    TVector<int> vec1(10, 1);
    vec1.resize(18, 2);

    TVector<int> vec2{ 1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2 };

    actual = (vec1 == vec2);

    return TestSystem::check(expected, actual) &&
        TestSystem::check(vec2.size(), vec1.size()) &&
        TestSystem::check(vec2.capacity(), vec1.capacity());
}

bool test_48_check_find_first_elem() {
    TVector<int> vec{2,4,6,8,4,8};
    int index = find_first_elem(vec, 2);

    return TestSystem::check(0, index);
}

bool test_49_check_find_first_elem_throw() {
    bool expected = true, actual = false;
    TVector<int> vec{ 9,8,7,6,5 };

    try {
        int index = find_first_elem(vec, 1);
    }
    catch (const std::exception& ex) {
        actual = true;
    }

    return TestSystem::check(expected, actual);
}

bool test_50_check_find_last_elem() {
    TVector<int> vec{ 88,99,111, 222, 99, 88 };
    int index = find_last_elem(vec, 88);

    return TestSystem::check(5, index);
}

bool test_51_check_find_last_elem_throw() {
    bool expected = true, actual = false;
    TVector<int> vec{ 9,8,7,6,5 };

    try {
        int index = find_last_elem(vec, 1);
    }
    catch (const std::exception& ex) {
        actual = true;
    }

    return TestSystem::check(expected, actual);
}

bool test_52_check_find_all_elems() {
    bool expected = true, actual = true;
    TVector<int> vec{ 88, 99, 111, 222, 99, 88 };
    TVector<int> pstns1(find_all(vec, 99));

    TVector<int> pstns2{1,4};

    actual = (pstns1 == pstns2);

    return TestSystem::check(expected, actual);
}

bool test_53_check_find_all_elems_throw() {
    bool expected = true, actual = false;
    TVector<int> vec{9,8,7,6,5};

    try {
        TVector<int> pstns = find_all(vec, 1);
    }
    catch (const std::exception& ex) {
        actual = true;
    }

    return TestSystem::check(expected, actual);
}

bool test_54_check_find_first_elem_ptr() {
    TVector<int> vec{2,5,8,1,2,4,8,9};
    int* pos = find_first_ptr(vec, 8);

    return TestSystem::check(vec.data() + 2, pos);
}

bool test_55_check_find_first_elem_ptr_throw() {
    bool expected = true, actual = false;
    TVector<int> vec{ 9,8,7,6,5 };

    try {
        int* i = find_first_ptr(vec, 1);
    }
    catch (const std::exception& ex) {
        actual = true;
    }

    return TestSystem::check(expected, actual);
}

bool test_56_check_find_last_elem_ptr() {
    TVector<int> vec{ 2,5,8,1,2,4,8,9 };
    int* pos = find_last_ptr(vec, 8);

    return TestSystem::check(vec.data() + 6, pos);
}

bool test_57_check_find_last_elem_ptr_throw() {
    bool expected = true, actual = false;
    TVector<int> vec{9,8,7,6,5};

    try {
        int* i = find_last_ptr(vec, 1);
    }
    catch (const std::exception& ex) {
        actual = true;
    }

    return TestSystem::check(expected, actual);
}

bool test_58_check_find_all_ptrs() {
    bool expected = true, actual = true;
    TVector<int> vec{ 2,5,8,1,2,4,8,9 };
    TVector<int*> ptrs1(find_all_ptrs(vec, 8));

    TVector<int*> ptrs2({ vec.data() + 2, vec.data() + 6 });

    actual = (ptrs1 == ptrs2);

    return TestSystem::check(expected, actual);
}

bool test_59_check_find_all_ptrs_throw() {
    bool expected = true, actual = false;
    TVector<int> vec{9,8,7,6,5};

    try {
        TVector<int*> i = find_all_ptrs(vec, 1);
    }
    catch (const std::exception& ex) {
        actual = true;
    }

    return TestSystem::check(expected, actual);
}

bool test_60_check_shuffle() {
    bool expected = true, actual = true;
    TVector<int> vec1{1,2,3,4,5};
    TVector<int> vec2(vec1);

    shuffle(vec1);
    actual = (vec1 != vec2);

    return TestSystem::check(expected, actual) &&
        TestSystem::check(vec2.size(), vec1.size()) &&
        TestSystem::check(vec2.capacity(), vec1.capacity());
}

bool test_61_check_sort() {
    bool expected = true, actual = true;
    TVector<int> vec1{8,3,7,1,5,4};
    hoara_sort(vec1);

    TVector<int> vec2{1,3,4,5,7,8};

    actual = (vec1 == vec2);

    return TestSystem::check(expected, actual) &&
        TestSystem::check(vec2.size(), vec1.size()) &&
        TestSystem::check(vec2.capacity(), vec1.capacity());
}

bool test_62_insert_after_delete() {
    bool expected = true, actual = true;
    int* mass = new int[100];
    for (int i = 0; i < 100; i++) {
        mass[i] = i + 1;
    }
    TVector<int> vec1(100, mass);
    vec1.erase(3);
    vec1.pop_front();
    vec1.pop_back();
    vec1.erase(3, 6);
    vec1.insert(4, 55);
    vec1.insert(6, { 33, 44, 55 });

    TVector<int> vec2({ 2, 3, 5, 12, 55, 13, 33, 44, 55, 14, 15,
        16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
        32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
        64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
        80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
        96, 97, 98, 99 });

    actual = (vec1 == vec2);

    return TestSystem::check(expected, actual);
}

bool test_63_replace_after_delete() {
    bool expected = true, actual = true;
    int* mass = new int[100];
    for (int i = 0; i < 100; i++) {
        mass[i] = i + 1;
    }
    TVector<int> vec1(100, mass);
    vec1.erase(3);
    vec1.pop_front();
    vec1.pop_back();
    vec1.erase(3);
    vec1.replace(4, 55);

    TVector<int> vec2({ 2, 3, 5, 7, 55, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
        33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
        49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64,
        65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
        81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96,
        97, 98, 99 });
    actual = (vec1 == vec2);
    return TestSystem::check(expected, actual);
}

bool test_64_insert_in_empty_vector() {
    bool expected = true, actual = true;
    TVector<int> vec1;
    vec1.push_front(1);
    TVector<int> vec2{ 1 };
    actual &= (vec1 == vec2);

    TVector<int> vec3;
    vec3.push_back(10);
    TVector<int> vec4{10};
    actual &= (vec3 == vec4);

    TVector<int> vec5;
    vec5.insert(0, 88);
    TVector<int> vec6{ 88 };
    actual &= (vec5 == vec6);
    return TestSystem::check(expected, actual);
}

bool test_65_replace_by_first_ptr() {
    bool expected = true, actual = true;
    TVector<int> vec1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 7, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
        34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
        52, 53, 54, 7, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
        69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
        7, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100 });
    vec1.replace(find_first_ptr(vec1, 9), 99);
    TVector<int> vec2({ 1, 2, 3, 4, 5, 6, 7, 8, 99, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 7, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
        34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
        52, 53, 54, 7, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
        69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
        7, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100 });
    actual = (vec1 == vec2);
    return TestSystem::check(expected, actual);
}

bool test_66_check_front_after_delete() {
    TVector<int> vec{ 1,2,3,4 };
    vec.pop_front();

    return TestSystem::check(2, vec.front());
}

bool test_67_check_back_after_delete() {
    TVector<int> vec{ 1,2,3,4,5,6 };
    vec.erase(3);
    vec.pop_back();
    vec.pop_back();
    return TestSystem::check(3, vec.back());
}

bool test_68_check_pop_front_after_delete() {
    bool expected = true, actual = true;
    TVector<int> vec1{ 1,2,3,4 }, vec2{3,4};
    vec1.pop_front();
    vec1.pop_front();
    actual = (vec1 == vec2);
    return TestSystem::check(expected, actual) &&
        TestSystem::check(vec2.size(), vec1.size()) &&
        TestSystem::check(vec2.capacity(), vec1.capacity());
}

int main() {
    TestSystem::start_test(test_1_create_default_vec, "test_1_create_default_vec");
    TestSystem::start_test(test_2_create_with_size, "test_2_create_with_size");
    TestSystem::start_test(test_3_create_with_array_and_size, "test_3_create_with_array_and_size");
    TestSystem::start_test(test_4_create_with_list, "test_4_create_with_list");
    TestSystem::start_test(test_5_create_with_copying, "test_5_create_with_copying");
    TestSystem::start_test(test_6_create_with_copying_throw, "test_6_create_with_copying_throw");
    TestSystem::start_test(test_7_create_with_size_and_array, "test_7_create_with_size_and_array");
    TestSystem::start_test(test_8_access_front_elem, "test_8_access_front_elem");
    TestSystem::start_test(test_9_access_front_elem_throw, "test_9_access_front_elem_throw");
    TestSystem::start_test(test_10_access_back_elem, "test_10_access_back_elem");
    TestSystem::start_test(test_11_access_back_elem_throw, "test_11_access_back_elem_throw");
    TestSystem::start_test(test_12_check_operator_equality_true, "test_12_check_operator_equality_true");
    TestSystem::start_test(test_13_check_operator_equlity_false, "test_13_check_operator_equlity_false");
    TestSystem::start_test(test_14_checl_operator_inequality_true, "test_14_checl_operator_inequality_true");
    TestSystem::start_test(test_15_check_operator_inequality_false, "test_15_check_operator_inequality_false");
    TestSystem::start_test(test_16_check_operator_brackets, "test_16_check_operator_brackets");
    TestSystem::start_test(test_17_check_operator_assign, "test_17_check_operator_assign");
    TestSystem::start_test(test_18_check_push_front, "test_18_check_push_front");
    TestSystem::start_test(test_19_check_push_front_with_reallocation_memory, "test_19_check_push_front_with_reallocation_memory");
    TestSystem::start_test(test_20_check_push_back, "test_20_check_push_back");
    TestSystem::start_test(test_21_check_push_back_with_reallocation_memory, "test_21_check_push_back_with_reallocation_memory");
    TestSystem::start_test(test_22_check_insert, "test_22_check_insert");
    TestSystem::start_test(test_23_check_insert_with_reallocation_memory, "test_23_check_insert_with_reallocation_memory");
    TestSystem::start_test(test_24_try_insert_throw, "test_24_try_insert_throw");
    TestSystem::start_test(test_25_check_pop_front, "test_25_check_pop_front");
    TestSystem::start_test(test_26_try_pop_front_throw, "test_26_try_pop_front_throw");
    TestSystem::start_test(test_27_check_pop_back, "test_27_check_pop_back");
    TestSystem::start_test(test_28_check_pop_back_throw, "test_28_check_pop_back_throw");
    TestSystem::start_test(test_29_check_erase, "test_29_check_erase");
    TestSystem::start_test(test_30_check_erase_throw, "test_30_check_erase_throw");
    TestSystem::start_test(test_31_check_replace, "test_31_check_replace");
    TestSystem::start_test(test_32_check_replace_after_deleted, "test_32_check_replace_after_deleted");
    TestSystem::start_test(test_33_check_replace_throw, "test_33_check_replace_throw");
    TestSystem::start_test(test_34_check_replace_ptr_throw, "test_34_check_replace_ptr_throw");
    TestSystem::start_test(test_35_check_replace_deleted_elem, "test_35_check_replace_deleted_elem");
    TestSystem::start_test(test_36_check_assign_with_size_value, "test_36_check_assign_with_size_value");
    TestSystem::start_test(test_37_check_assign_with_array, "test_37_check_assign_with_array");
    TestSystem::start_test(test_38_check_assgin_with_reallocation_memory, "test_38_check_assgin_with_reallocation_memory");
    TestSystem::start_test(test_39_try_access_to_elem_out_of_range, "test_39_try_access_to_elem_out_of_range");
    TestSystem::start_test(test_40_check_clear, "test_40_check_clear");
    TestSystem::start_test(test_41_check_reserve_with_less_cap, "test_41_check_reserve_with_less_cap");
    TestSystem::start_test(test_42_check_reserve_with_bigger_cap, "test_42_check_reserve_with_bigger_cap");
    TestSystem::start_test(test_43_check_resize_with_less_size, "test_43_check_resize_with_less_size");
    TestSystem::start_test(test_44_check_resize_with_less_size_cap, "test_44_check_resize_with_less_size_cap");
    TestSystem::start_test(test_45_check_resize_with_bigger_size, "test_45_check_resize_with_bigger_size");
    TestSystem::start_test(test_46_check_resize_with_bigger_size_cap, "test_46_check_resize_with_bigger_size_cap");
    TestSystem::start_test(test_47_check_resize_with_value, "test_47_check_resize_with_value");
    TestSystem::start_test(test_48_check_find_first_elem, "test_48_check_find_first_elem");
    TestSystem::start_test(test_49_check_find_first_elem_throw, "test_49_check_find_first_elem_throw");
    TestSystem::start_test(test_50_check_find_last_elem, "test_50_check_find_last_elem");
    TestSystem::start_test(test_51_check_find_last_elem_throw, "test_51_check_find_last_elem_throw");
    TestSystem::start_test(test_52_check_find_all_elems, "test_52_check_find_all_elems");
    TestSystem::start_test(test_53_check_find_all_elems_throw, "test_53_check_find_all_elems_throw");
    TestSystem::start_test(test_54_check_find_first_elem_ptr, "test_54_check_find_first_elem_ptr");
    TestSystem::start_test(test_55_check_find_first_elem_ptr_throw, "test_55_check_find_first_elem_ptr_throw");
    TestSystem::start_test(test_56_check_find_last_elem_ptr, "test_56_check_find_last_elem_ptr");
    TestSystem::start_test(test_57_check_find_last_elem_ptr_throw, "test_57_check_find_last_elem_ptr_throw");
    TestSystem::start_test(test_58_check_find_all_ptrs, "test_58_check_find_all_ptrs");
    TestSystem::start_test(test_59_check_find_all_ptrs_throw, "test_59_check_find_all_ptrs_throw");
    TestSystem::start_test(test_60_check_shuffle, "test_60_check_shuffle");
    TestSystem::start_test(test_61_check_sort, "test_61_check_sort");
    TestSystem::start_test(test_62_insert_after_delete, "test_62_insert_after_delete");
    TestSystem::start_test(test_63_replace_after_delete, "test_63_replace_after_delete");
    TestSystem::start_test(test_64_insert_in_empty_vector, "test_64_insert_in_empty_vector");
    TestSystem::start_test(test_65_replace_by_first_ptr, "test_65_replace_by_first_ptr");
    TestSystem::start_test(test_66_check_front_after_delete, "test_66_check_front_after_delete");
    TestSystem::start_test(test_67_check_back_after_delete, "test_67_check_back_after_delete");
    TestSystem::start_test(test_68_check_pop_front_after_delete, "test_68_check_pop_front_after_delete");
    TestSystem::print_final_info();
    return 0;
}