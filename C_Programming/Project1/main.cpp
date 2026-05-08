#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "user.h"
#include "sort.h"
#include "factory.h"

int main() {
    // 1. 데이터 준비
    std::vector<std::string> students = {
        "Kim", "Lee", "Park", "Choi", "Jung", "Kang", "Cho", "Yoon", "Jang", "Lim",
        "Han", "Oh", "Seo", "Shin", "Kwon", "Hwang", "Song", "An", "Jeon", "Hong",
        "Yoo", "Goh", "Moon", "Yang", "Son", "Bae", "Baek", "Heo", "Yoo", "Nam"
    };

    // 2. User 객체 동적 할당 (사용자 요청 방식)
    User* user = new User;

    // 3. Factory 객체 선언
    // 이제 factory는 정렬 객체를 찍어내는 인스턴스 역할을 합니다.
    SortFactory factory;

    std::cout << "=== 시스템 가동: 파일 시스템 시나리오 ===" << std::endl;

    // 4. 팩토리 객체를 통해 QSort 생성 및 주입
    // factory.createSort는 unique_ptr을 반환합니다.
    auto qSort = factory.createSort(SortFactory::Type::Quick);
    user->setSortStrategy(std::move(qSort)); // 소유권 이전
    user->Sort(students);

    std::cout << "\n=== 시스템 가동: 저사양 환경 시나리오 ===" << std::endl;

    // 5. 팩토리 객체를 통해 BSort 생성 및 주입
    auto bSort = factory.createSort(SortFactory::Type::Bubble);
    user->setSortStrategy(std::move(bSort)); // 전략 교체
    user->Sort(students);

    // 6. 결과 확인 및 메모리 해제
    std::cout << "\n[최종 정렬 결과]" << std::endl;
    for (const auto& name : students) {
        std::cout << name << " ";
    }
    std::cout << std::endl;

    delete user; // new로 생성했으므로 명시적 삭제

    return 0;
}