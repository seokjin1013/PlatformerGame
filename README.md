## 개요

C++20과 콘솔창 출력으로만 만든 플랫포머 게임입니다.

세종대학교 2021년 2학기 SW설계 및 기초 과목을 수강하면서 만든 4인 팀 프로젝트입니다.

앞으로의 업데이트는 없을 예정입니다. (2021.12.22.)

## 역할 분담

### 내가 한 부분

1. BulletBlock, Player 시간역행 부분 버그 수정
2. LaserBlock 리뉴얼
3. 그외 모든 것 (Block, BreakableBlock, Button, ButtonBlock, Console, Controller, FlickingBlock, Follower, GuiButton, HowToPlay, HowToPlayPlayerClone, Information, Particle, Player 나머지(충돌처리, 조작 관련 등), PlayManager, Room, RoomConstructor, Sprite, SpriteImporter, StageSelection, Sticker, Title, View)
4. Battery, Block, BreakableBlock, Button, ButtonBlock, FlickingBlock, Goal, GuiLevelButton, GuiMenuButton, HowToPlay*, Information*, Pause, Player, PlayerJump, StageSelection*, Star, Text* 의 bmp파일 디자인
5. 1~5스테이지 레벨 디자인

### 팀원께서 해주신 부분

1. Battery, Bullet, BulletBlock, Goal, Key, LaserBlock, Player 시간역행 부분 초기 커밋
2. 6~20스테이지 레벨 디자인
3. Bullet, BulletBlock, LaserBlock, PlayerDie의 bmp파일 디자인

6 ~10, 16 ~20스테이지를 디자인해주신 팀원 분의 허락을 받지 않아 해당 스테이지는 제거하였습니다.

## 실행

코드는 **visual studio**로 빌드합니다.

새 프로젝트를 만들고 cpp는 소스파일, hpp와 inl은 헤더파일에 **추가>기존항목** 을 통해 추가하고, bmp는 프로젝트 폴더에 같이 넣어둡니다.

프로젝트 설정은 C++언어 표준을 **ISO C++20 표준(/std:c++20)** 으로 설정하고 SDL 검사를 **아니오(/sdl-)** 로 설정합니다.

## 게임

다음은 시작화면입니다.

![image](https://user-images.githubusercontent.com/63408412/147127283-f77a3257-da90-46f3-8651-22c4fa6796ae.png)

START를 선택해 스테이지 선택 화면으로 갈 수 있고 HOW를 선택해 조작 방법을 간략히 알아볼 수 있습니다.

다음은 스테이지 선택화면입니다.

![image](https://user-images.githubusercontent.com/63408412/146978418-0681d3dd-15f2-460c-85bb-81551c7291ef.png)

4개의 난이도로 각각 5개의 스테이지가 있습니다. 튜토리얼 스테이지를 모두 클리어하면 각 난이도마다 첫 번째 스테이지인 6, 11, 16 스테이지가 열립니다.

다음은 조작 방법을 알아보는 화면입니다.

![image](https://user-images.githubusercontent.com/63408412/147127389-37bf1df3-c58a-490c-a2f8-c9e8cf8b08ea.png)

이해가 되기 쉽도록 애니메이션을 통해 보여드립니다.

스테이지의 자세한 완료 방법은 튜토리얼 스테이지의 표지판에 가까이 가면 알려줍니다.

![image](https://user-images.githubusercontent.com/63408412/146978994-eb94f542-4f2d-44d1-afcd-3ec8c56423a1.png)

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

## 버그

1. sprite를 회전해서 출력해도 충돌범위는 변하지 않습니다.
2. 첫 화면에서 shift를 누르면 메뉴를 선택했을 때 모션이 이상하게 나옵니다.

1번 버그는 심각한 버그이지만 현재 충돌 처리를 하는 모든 스프라이트는 정사각형이어서 플레이 하는 데에 지장은 없습니다.
