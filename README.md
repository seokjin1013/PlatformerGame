## 구조

```bash
.
|-- ExecuteFile
|   |-- *.bmp (108개)
|   |-- PlatformerGame.exe
|-- PlatformerGame
|   |-- *.cpp (31개)
|   |-- *.hpp (34개)
|   |-- *.bmp (108개)
|   |-- *.inl (3개)
`-- README.md

```

### 게임 실행만 해보고 싶을 때

ExecuteFile 폴더만 내려받아 bmp파일을 그대로 두고 Platformer.exe를 실행하세요.

콘솔창의 문제가 있을 경우 [문제 해결](#문제-해결)을 참고하세요.

### 코드를 빌드하고 싶을 때

PlatformerGame 폴더만 내려받으세요. **Visual Studio**로 개발했기 때문에 Visual Studio로 빌드하겠습니다.

1. 새 프로젝트를 만들고 cpp, hpp, inl, bmp를 모두 **프로젝트 폴더**에 넣습니다.

2. cpp는 소스파일, hpp와 inl은 헤더파일, bmp는 리소스파일에 **추가>기존항목** 을 통해 추가합니다.

3. 프로젝트 설정은 C++언어 표준을 **ISO C++20 표준(/std:c++20)** 으로 설정하고 SDL 검사를 **아니오(/sdl-)** 로 설정합니다.

4. Ctrl + F5로 실행합니다.

콘솔창의 문제가 있을 경우 [문제 해결](#문제-해결)을 참고하세요.

## 개요

C++20과 콘솔창 출력으로만 만든 플랫포머 게임입니다.

세종대학교 2021년 2학기 SW설계 및 기초 과목을 수강하면서 만든 4인 팀 프로젝트입니다.

앞으로의 업데이트는 없을 예정입니다. (2021.12.22.)

## 게임

### 메뉴

다음은 시작화면입니다. START를 선택해 스테이지 선택 화면으로 갈 수 있습니다.

![start](https://user-images.githubusercontent.com/63408412/151660295-d96e2462-429d-405d-91b4-e14104c85818.gif)

다음은 조작 방법을 알아보는 화면입니다. HOW를 선택해 확인할 수 있습니다.

![how_to_play](https://user-images.githubusercontent.com/63408412/151664206-7db378d5-490c-437f-92cf-a69c7674202d.gif)

### 기본 규칙

튜토리얼 스테이지에는 표지판을 읽어가며 진행할 수 있습니다.

![key](https://user-images.githubusercontent.com/63408412/151660399-190bfc9d-6686-42c7-b771-5c3f32f33e43.gif)

스테이지를 클리어하기 위해서는 열쇠를 먼저 찾아야합니다.

![battery_flag](https://user-images.githubusercontent.com/63408412/151660423-67aa24aa-4e8e-4acc-980c-43653f419157.gif)

그 다음 깃발을 찾아가면 클리어입니다. 중간에 추가점수 요소인 배터리가 있습니다.

획득한 배터리의 수만큼 클리어했을 시 받게되는 별의 수가 늘어납니다.

### 시간 역행

플레이어는 **시간 역행 기술**을 사용할 수 있습니다. 사용 시 에너지 바가 표시되고 에너지가 모두 소진되면 안 됩니다. 시간이 지나면 다시 회복됩니다.

![time_recall](https://user-images.githubusercontent.com/63408412/151660479-9e7888a7-21ea-44bb-a895-c66afd56d640.gif)

이를 통해 어려운 지점의 배터리나 깃발에 도달하여 고득점을 노려보세요.

다음과 같은 세세한 조작이 요구되기도 합니다.

![various_difficulty](https://user-images.githubusercontent.com/63408412/151660517-c2621bfb-761a-4842-b0da-8b5f09d19c4f.gif)

쉬운 스테이지부터 아주 어려운 스테이지까지 다양한 난이도가 준비되어 있습니다.

## 원리

콘솔창의 크기를 고정하고, 가장 출력 속도가 빠른 fwrite함수를 통해 전체 스크린을 초당 60회씩 출력합니다.

1. Object는 화면에 그려지는 모든 사물들의 부모입니다.
2. Room은 여러 Object들을 가리키는 포인터를 갖고 있습니다.
3. PlayManager::play 함수에서 모든 과정이 일어납니다.
4. Console::frame_skip_or_waiting 함수를 통해 프레임 스킵이 구현되고 있습니다.
5. 키 입출력은 Controller가 담당합니다.
6. 화면 출력은 View와 Console이 담당합니다.
7. PlayManager에서 게임 세이브와 로드를 합니다.
8. SpriteImporter는 픽셀 당 비트수가 24인 bmp파일을 읽어 색상값을 추출합니다.

## 역할 분담

### [Yoon-SeokJin](https://github.com/Yoon-SeokJin)이 한 부분

1. Block, BreakableBlock, Button, ButtonBlock, Console, Controller, FlickingBlock, Follower, GuiButton, HowToPlay, HowToPlayPlayerClone, Information, Particle, Player 나머지(충돌처리, 조작 관련 등), PlayManager, Room, RoomConstructor, Sprite, SpriteImporter, StageSelection, Sticker, Title, View 관련 구현
2. Battery, Block, BreakableBlock, Button, ButtonBlock, FlickingBlock, Goal, GuiLevelButton, GuiMenuButton, HowToPlay*, Information*, Pause, Player, PlayerJump, StageSelection*, Star, Text* 의 bmp파일 디자인
3. BulletBlock, Player 시간역행 부분 버그 수정
4. LaserBlock 리뉴얼
5. 1~5스테이지 레벨 디자인

### 팀원께서 해주신 부분

1. Battery, Bullet, BulletBlock, Goal, Key, LaserBlock, Player 시간역행 부분 초기 커밋
2. 6~20스테이지 레벨 디자인
3. Bullet, BulletBlock, LaserBlock, PlayerDie의 bmp파일 디자인

**6 ~10, 16 ~20스테이지를 디자인해주신 팀원 분의 허락을 받지 않아 해당 스테이지는 제거하였습니다. 조건을 만족하여도 자물쇠가 풀리지 않는 것은 버그가 아닙니다.

## 버그

1. sprite를 회전되어도 충돌범위가 반영되지 않습니다.
2. 첫 화면에서 shift를 누르면 메뉴를 선택했을 때 모션이 이상하게 나옵니다.

현재 충돌 처리를 하는 모든 스프라이트는 정사각형이기 때문에 1번 버그 때문에 정상적인 플레이가 불가능한 점은 없습니다.

## 문제 해결

### 콘솔창 설정

![cmd_setting1](https://user-images.githubusercontent.com/63408412/151655508-cd7b7c7a-1ac8-49c6-96fd-01967402eacf.jpg)
![cmd_setting2](https://user-images.githubusercontent.com/63408412/151655509-cb5af60f-1a82-4915-b708-57c9f97de5e5.jpg)

콘솔창 설정은 이렇게 되어있을 때 게임이 정상적으로 실행됩니다.

### 오류메시지

#### 실행 시 The save file is corrupt.가 출력될 때

Recall_Save_Data.txt가 정상적인 플레이로 달성할 수 없는 상태이며 임의로 수정했음을 의미합니다. Recall_Save_Data.txt를 수정 전의 상태로 돌려주시거나 삭제해주세요. (삭제하면 그동안 플레이했던 기록이 사라집니다.)

#### 실행 시 file extension is not bitmap가 출력될 때

bmp파일이 누락되었음을 의미합니다. bmp파일을 다시 내려받아 덮어씌워주세요.

#### 실행 시 bitmap file bit_count is not 24가 출력될 때

bmp파일의 비트 수가 변형되었음을 의미합니다. bmp파일의 비트 수를 24로 맞춰주시거나 bmp파일을 다시 내려받아 덮어씌워주세요.

#### 실행 시 unexpected image size. fit image size to previous index image size.가 출력될 때

bmp파일의 (이름)(숫자).bmp 형식에서 이름이 같은 bmp파일끼리의 이미지 크기가 다름을 의미합니다. 통일시켜주시거나 bmp파일을 다시 내려받아 덮어씌워주세요.
