#include <iostream>
#include "Set.h"   

struct Tester {
    int passed = 0, failed = 0;
    void expect(bool cond, const std::string& msg) {
        if (cond) { ++passed; std::cout << "[PASS] " << msg << "\n"; }
        else      { ++failed; std::cout << "[FAIL] " << msg << "\n"; }
    }
    void summary() const {
        std::cout << "\n==============================\n";
        std::cout << "Tests passed: " << passed << "\n";
        std::cout << "Tests failed: " << failed << "\n";
        std::cout << "==============================\n";
    }
};

template <typename T>
static bool containsAll(const Set<T>& s, const std::vector<T>& vals) {
    for (const auto& v : vals) if (!s.contains(v)) return false;
    return true;
}

static void demo_AB_output() {
    // Build A and B with the exact elements (in insertion order for printing)
    Set<int> A;
    A.insert(10);
    A.insert(34);
    A.insert(4);
    A.insert(7);
    A.insert(8);

    Set<int> B;
    B.insert(3);
    B.insert(5);
    B.insert(11);
    B.insert(8);

    // Print A and B
    std::cout << "A: " << A << "\n";
    std::cout << "B: " << B << "\n";

    // Membership checks
    std::cout << (B.contains(5)  ? "5 is a member of B"  : "5 is not a member of B") << "\n";
    std::cout << (A.contains(11) ? "11 is a member of A" : "11 is not a member of A") << "\n";

    // Sizes and comparisons
    std::cout << "Size of B is " << B.size() << "\n";
    std::cout << ((A.size() == B.size()) ? "A and B are same size!" : "A and B are not same size!") << "\n";
    std::cout << (B.subsetOf(A) ? "B is a subset of A" : "B is not a subset of A") << "\n";
    std::cout << ((A == B) ? "A and B are equal!" : "A and B are not equal!") << "\n";

    // Set operations (use identities so we don't depend on a particular symmetric-diff operator)
    Set<int> U  = A | B;                 // Union
    Set<int> I  = A & B;                 // Intersection
    Set<int> D  = A - B;                 // Difference A-B
    Set<int> SD = (A - B) | (B - A);     // Symmetric difference via identity

    std::cout << "Union of A and B (A ∪ B): " << U  << "\n";
    std::cout << "Intersection of A and B (A ∩ B): " << I  << "\n";
    std::cout << "Difference of A and B (A-B): " << D  << "\n";
    std::cout << "Symmetric Difference of A and B (AΔB): " << SD << "\n";

    Set<int> left = (A - B) | B;
    std::cout << "(A-B) ∪ B: " << left << "\n";
    std::cout << ((U == left) ? "(A ∪ B) and (A-B) ∪ B are equal!"
                              : "(A ∪ B) and (A-B) ∪ B are NOT equal!") << "\n";

    Set<int> sdb = (A - B) | (B - A);
    std::cout << "(A-B) ∪ (B-A): " << sdb << "\n";
    std::cout << ((SD == sdb) ? "(AΔB) and (A-B) ∪ (B-A) are equal!"
                              : "(AΔB) and (A-B) ∪ (B-A) are NOT equal!") << "\n";
}


void run_int_tests(Tester& test) {
    std::cout << "\n===== Set<int> tests =====\n";

    // Construction
    Set<int> A;
    Set<int> B{1,2,3,4};
    Set<int> C{3,4,5,6};
    Set<int> D(B);

    test.expect(A.size() == 0, "default constructed is empty");
    test.expect(B.size() == 4, "list-init size is 4");
    test.expect(D == B,        "copy-constructed equals original");

    std::cout << "A = " << A << "\n";
    std::cout << "B = " << B << "\n";
    std::cout << "C = " << C << "\n";
    std::cout << "D = " << D << "\n\n";

    // Insert / remove / contains
    test.expect(A.insert(10),  "insert new element");
    test.expect(!A.insert(10), "duplicate insert returns false");
    test.expect(A.contains(10),"contains inserted element");
    test.expect(!A.contains(99),"does not contain non-existent");
    test.expect(A.size() == 1, "size after insert is 1");
    test.expect(A.remove(10),  "remove existing element");
    test.expect(!A.remove(10), "remove again returns false");
    test.expect(A.size() == 0, "size back to 0");

    // Clear / assignment / duplicates in list-init
    Set<int> E{7,7,7,8,9};
    test.expect(E.size() == 3, "duplicates ignored in list-init");
    E.clear();
    test.expect(E.size() == 0, "clear empties set");

    E = C;
    test.expect(E == C, "assignment operator copies set");

    // Subset / equality
    Set<int> X{1,2};
    Set<int> Y{1,2,3};
    Set<int> Z{3,2,1};
    test.expect(X.subsetOf(Y),     "X ⊆ Y");
    test.expect(!(Y.subsetOf(X)),  "Y ⊄ X");
    test.expect(Y.equals(Z),       "Y equals Z (order-insensitive)");
    test.expect(!(X == Z),         "X != Z");
    test.expect((X <= Y),          "operator<= subset true");
    test.expect(!(Y <= X),         "operator<= subset false");
    test.expect((Y == Z),          "operator== equality true");
    test.expect((X != Z),          "operator!= non-equality true");

    // Member ops
    Set<int> U  = B.unionWith(C);
    Set<int> I  = B.intersectionWith(C);
    Set<int> DF = B.differenceWith(C);
    Set<int> SD = B.symmetricDifferebceWith(C); // rename here if your method name differs

    std::cout << "B ∪ C = " << U  << "\n";
    std::cout << "B ∩ C = " << I  << "\n";
    std::cout << "B - C = " << DF << "\n";
    std::cout << "B Δ C = " << SD << "\n";

    test.expect(containsAll(U,  {1,2,3,4,5,6}) && U.size() == 6, "union has all unique elements");
    test.expect(containsAll(I,  {3,4})          && I.size() == 2, "intersection is {3,4}");
    test.expect(containsAll(DF, {1,2})          && DF.size() == 2, "difference B-C is {1,2}");
    test.expect(containsAll(SD, {1,2,5,6})      && SD.size() == 4, "symm diff BΔC is {1,2,5,6}");

    // Operator overloads
    Set<int> U2  = B | C;
    Set<int> I2  = B & C;
    Set<int> DF2 = B - C;
    Set<int> SD2 = B / C;

    test.expect(U2 == U,   "operator| matches unionWith");
    test.expect(I2 == I,   "operator& matches intersectionWith");
    test.expect(DF2 == DF, "operator- matches differenceWith");
    test.expect(SD2 == SD, "operator/ matches symmetricDifferenceWith");

    // Compositions / identities
    Set<int> comp1 = (B - C) | C;
    test.expect(comp1 == (B | C), "(B - C) ∪ C == B ∪ C");

    Set<int> comp2 = (B - C) | (C - B);
    test.expect(comp2 == (B / C), "(B - C) ∪ (C - B) == B Δ C");

    test.expect((I2 <= B) && (I2 <= C), "intersection subset of both");

    // Edge cases
    Set<int> Empty;
    Set<int> Ue  = Empty.unionWith(Empty);
    Set<int> Ie  = Empty.intersectionWith(Z);
    Set<int> Dfe = Z.differenceWith(Empty);
    Set<int> SDe = Empty.symmetricDifferebceWith(Z);

    test.expect(Ue.size() == 0, "∅ ∪ ∅ = ∅");
    test.expect(Ie.size() == 0, "∅ ∩ Z = ∅");
    test.expect(Dfe == Z,       "Z - ∅ = Z");
    test.expect(SDe == Z,       "∅ Δ Z = Z");

    Set<int> S1{9,10};
    test.expect((S1 | S1) == S1, "idempotence union");
    test.expect((S1 & S1) == S1, "idempotence intersection");

    Set<int> disjoint{100,101};
    test.expect((B & disjoint).size() == 0, "disjoint intersection empty");

    Set<int> chain = ((B - C) | (C - B)) & (B | C);
    test.expect(chain == (B / C), "chain identity: ((B-C)|(C-B)) & (B|C) = B Δ C");
}

void run_string_tests(Tester& test) {
    std::cout << "\n===== Set<std::string> tests =====\n";

    Set<std::string> S1{"apple","banana"};
    Set<std::string> S2{"banana","cherry"};
    Set<std::string> S3(S1);

    test.expect(S3 == S1, "copy equals original");
    test.expect(!S1.insert("banana"), "duplicate insert returns false");
    test.expect(S1.insert("date"),    "unique insert returns true");
    test.expect(S1.contains("date"),  "contains newly inserted");

    auto SU  = S1 | S2;
    auto SI  = S1 & S2;
    auto SDf = S1 - S2;
    auto Ssd = S1 / S2;

    test.expect(SI.contains("banana") && SI.size() == 1, "intersection is {banana}");
    test.expect(SU.contains("apple") && SU.contains("cherry"), "union contains ends");
    test.expect(!SDf.contains("banana"), "difference removes common element");
}

int main() {
    Tester t;
    run_int_tests(t);
    run_string_tests(t);
    t.summary();
    std::cout << "=========================================================" << std::endl;
    std::cout << "        Testing Complete Starting Expected Output        " << std::endl;
    std::cout << "=========================================================" << std::endl;
    demo_AB_output();

    
    return (t.failed == 0) ? 0 : 1;
}
