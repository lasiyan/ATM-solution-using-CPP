# Cpp-ATM-Solution

Making ATM Program based on object oriented programming using c++. This composed on clientATM and adminATM. ClientATM is real ATM machine object like what we known. And adminATM is like bank. This project implemented in VisualStudion 2015.

ATM solution은 실생활에서 사용하는 ATM의 기능을 객체지향을 활용하여 구현한 것으로 사용자가 이용하는 ATM, clientATM의 기본 기능 4가지인 예금 조회, 예금 인출, 입금, 계좌 이체를 위한 계좌를 생성하고, 관리하는 클래스 adminATM을 추가하였다. 이 두 ATM의 공통 속성을 묶어 mainATM을 생성하여 프로그램을 실행한다.

## 개발 환경

* OS : Windows 10 Pro 64bit
* CPU : Intel(R) Core(TM) i5-5200U CPU @ 2.20GHz 2.20 GHz
* RAM : 4.00GB
* IDE : Microsoft Visual Studio Community 2015

## 사용 기술

C++ class, STL vector, Basic Excel Library

## 부가 설명

 프로젝트는 크게 3가지 파트로 구성되는데 ATM의 기능을 처리하는 (main, client, admin)ATM 부분, 그리고 클라이언트의 요청을 DB에서 처리하는 fileControl클래스(DAO), 마지막으로 ATM과 DAO 클래스 사이에서 데이터를 전달하고 저장하는 객체 DO 클래스가 있다.

 mainATM은 사용자와 관리자 기능을 수행하는 clientATM과 adminATM의 부모 클래스로 두 클래스의 공통 속성과 메서드를 묶어서 만든 클래스이다. 따라서 두 클래스는 mainATM을 상속 받아 구현되는, 상속성과 다형성의 개념을 담고 있다.

 client 클래스는 fileControl 클래스에서 처리된 또는 처리할 데이터를 저장하는 객체로 사용자가 ATM에서 입력한 데이터들이 저장되거나 fileControl에서 불러온 데이터들이 저장되는, 일종의 자바로 따지면 빈즈클래스와 유사한 기능을 담당한다. 모든 속성들은 private 접근 권한자로 구성되며, 메서드는 생성자를 제외하고는 get과 set메서드로만 구현되어 정보의 캡슐화를 실현하고 이를 통해 정보 은닉, 즉 보안성와 안정성을 향상시킨다.

 fileControl 클래스는 DAO 역할을 하는 클래스로 DB(여기서는 Excel)파일에 접근하여 데이터를 검색하거나 삽입, 삭제와 같은 DML적 처리를 수행한다. 이 클래스는 반드시 ATM클래스의 정보가 아닌 ATM클래스들에서 client 객체로 정보를 저장하면 client 객체의 정보만 get 메서드를 통해 참조해야하며 ATM클래스들과의 직접적인 정보의 교환은 불가능하도록 설계하였다. 

## 실행 과정

1. ATM_solution.zip 파일을 다운로드 후 압축 해제
2. 새 프로젝트 - 프로젝트 생성 옵션에서 SDL 체크 헤제
3. .cpp파일과 .h파일 추가 후 실행

## 실행 결과

[![Demo Doccou alpha](https://j.gifs.com/pgmEWr.gif)](https://youtu.be/82eeOi0Esrg)

(클릭 시 유튜브로 이동합니다)
