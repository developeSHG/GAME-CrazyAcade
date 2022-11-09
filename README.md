# GAME-CrazyAcade
[Win API 2D - Individual Project] 크레이지아케이드


동영상(Client)    : https://www.youtube.com/watch?v=_zshmuKgud0

동영상(Tool)      : https://www.youtube.com/watch?v=zNB4gyvFYEs

장르              : 액션

날짜              : 2019.05.01 ~ 2019.05.15

인원              : 1명

개발 환경         : Visual Studio 2015 (x64)

개발 언어 및 도구  : C++, Windows API


================================================================
*설명*

타일 형식의 맵을 Tool로 찍어서 지면 충돌 구현
- 아틀라스 텍스처(Atlas Texture)의 픽셀 인덱스를 이용한 맵 툴 제작

Scene별로 리소스를 나눠 효율적으로 관리하며 각각 세이브/로드 구현
- 로고, 메뉴, 튜토리얼, 스테이지 총 7개의 Scene 구현

게임 내 오브젝트들을 하나의 매니저를 통해 관리
- 게임 내 모든 오브젝트를 하나의 베이스 클래스에서 파생시켜 Mediator 및 Iterator 패턴을 이용해 관련 클래스의 처리를 하나의 클래스에서 조작/관리
