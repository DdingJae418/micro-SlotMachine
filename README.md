# ATMEGA128 슬롯 머신 게임기

# ⌜ 개요 ⌟

현대의 디지털 슬롯 머신은 플레이어가 버튼을 누른 순간 RNG(Random Number Generator)로 숫자를 생성하여 모든 릴(reel)의 결과를 곧바로 정한다. 이러한 방식에서는 순전히 운에 따라 당첨 여부가 결정되므로, 옛날 기계식 슬롯 머신의 동작 방식에 착안하여, 좀 더 플레이어가 결과에 개입할 수 있는 슬롯 머신 게임기를 만들어 보고자 하였다.

JKIT-128-1 실습 키트를 사용하여 개발을 진행하였으며, 내장된 부품 중 부저, FND 인터페이스, 스위치를 사용하였다. 부저를 통해 게임 노래, 효과음을 출력하고, FND를 사용해 게임 화면을 출력하였다. 스위치를 눌러 게임을 진행하거나 초기화 할 수 있도록 하였다.

# ⌜ 기능 구현 ⌟

## 1. 고정 속도 갱신

<div align="center">
    <img src="/media/class_diagram1.png" alt="그림1. 클래스 다이어그램" width="70%">
    <p>그림1. 클래스 다이어그램</p>
</div>

- FNDController 및 BuzzerController 클래스를 사용하여 애니메이션 및 게임 음악을 재생하기 위해서는 고정된 시간 주기로 상태를 갱신할 필요가 있었다.
- SwitchController에서 스위치 입력을 감지하고, GameManager에서 게임 진행 상태를 초 단위로 관리하기 위해서도 고정된 시간 주기로 상태를 갱신할 필요가 있었다.
- 애니메이션 및 음악 재생, 스위치 입력 감지, 게임 상태 변화가 모두 동기화되어 진행될 필요가 있었기 때문에, 각 구성 요소를 일관성 있게 관리하는 클래스가 필요했다.
- 그에 따라 FixedRateUpdater 클래스를 활용하여 고정 속도(60프레임)로 등록된 객체(UpdateListener)들을 호출할 수 있도록 구현했다. 결과적으로 구성 요소들이 고정된 시간 주기로 실행되었다.

```cpp
// lib/manager/fixed_rate_updater.cpp 코드 일부
float Time::DeltaTime()
{
    static float frame = FixedRateUpdater::GetInstance().GetFrameRate();
    return 1 / frame;
}
```
- 속도는 동적으로 변경이 가능하며, Time 클래스를 사용하여 다른 클래스에서도 쉽게 단위 시간을 사용할 수 있도록 하였다.

## 2. FND 애니메이션 재생

<div align="center">
    <table>
        <tr>
            <td align = "center">
                <img src="/media/swipe_animation.gif" alt="영상1. Swipe 애니메이션">
                <p>영상1. Swipe 애니메이션</p>
            </td>
            <td align = "center">
                <img src="/media/flicker_animation.gif" alt="영상2. Flicker 애니메이션">
                <p>영상2. Flicker 애니메이션</p>
            </td>
            <td align = "center">
                <img src="/media/round_robin_animation.gif" alt="영상3. Round Robin 애니메이션">
                <p>영상3. Round Robin 애니메이션</p>
            </td>
        </tr>
        <tr>
            <td align = "center">
                <img src="/media/write_animation.gif" alt="영상4. Write 애니메이션">
                <p>영상4. Write 애니메이션</p>
            </td>
            <td align = "center">
                <img src="/media/flicker_and_swipe_animation.gif" alt="영상5. Flicker + Swipe 애니메이션">
                <p>영상5. Flicker + Swipe 애니메이션</p>
            </td>
            <td align = "center">
                <img src="/media/sequential_output.gif" alt="영상6. 디지트 순차 출력">
                <p>영상6. 디지트 순차 출력</p>
            </td>
        </tr>
    </table>
</div>

- FND 화면의 4개 디지트를 활용하여 Swipe, Flicker, Round Robin, Write 등의 애니메션을 구현하였다.

```cpp
// lib/output/fnd_controller.cpp 코드 일부
void FNDController::StartAnimation(Animation animation, float speed, int start, int end)
{
    // Start animation
    FNDAnimation* startingAnimation = animationMap[animation];
    startingAnimation->StartAnimation(speed, start, end);
    playingAnimations.push_back(startingAnimation);
}
```

- 디지트를 부분적으로 선택하여 각 디지트마다 개별적인 애니메이션을 재생할 수 있도록 설계하였다. 애니메이션 재생을 요청할 때, 시작 디지트 번호 start와 끝 디지트 번호 end를 매개변수로 전달하여 해당 범위의 디지트에만 해당 애니메이션을 재생하도록 하였다.
- 영상5의 경우 첫번째 디지트에서는 Flicker 애니메이션, 두번째 디지트부터는 Swipe 애니메이션을 재생하고 있다.

## 3. 벡터를 활용한 음악 및 효과음 관리

```cpp
// include/sounds.h 코드 일부
using BuzzerSound = std::vector<std::pair<double, float>>;
using NoteIter = BuzzerSound::const_iterator;

...

// lib/output/buzzer_controller.cpp 코드 일부
void BuzzerController::StartSound(const BuzzerSound* sound, float speed, bool loop)
{
    if(isMute) return;

    currentSound = sound;
    playSpeed = speed;
    loopSound = loop;
    playTime = 0;

    // Play first note
    if (currentSound) 
    {
        currentNote = currentSound->begin();
        PlayNote(currentNote->first);
    }
}

void BuzzerController::Update()
{
    if (!currentSound) return;

    playTime += playSpeed * Time::DeltaTime();
    if (playTime >= currentNote->second)
    {
        currentNote++;

        if (currentNote == currentSound->end()) 
        // Playing complete
        {
            if (loopSound) 
                StartSound(currentSound, playSpeed, true);
            else 
            {
                currentSound = nullptr;
                PlayNote(NOTE_REST);
            }
        }
        else
        // Play next note
        {
            PlayNote(currentNote->first);
            playTime = 0;
        }
    }
}
```
- 게임 음악의 음계를 순차적으로 읽어가며 특정 시간동안 출력하는 기능을 효율적으로 관리하고자 하였다.
- 사용 편리성과 성능을 고려하여 STL 벡터 컨테이너를 선택하였고, BuzzerSound와 NoteIter를 선언하여 반복자로 쉽게 음계를 읽어들일 수 있도록 설계하였다.
- BuzzerSound 컨테이너에는 음계와 음표의 길이가 쌍(pair)으로 저장되어 활용된다. 

## 4. 상태 패턴 활용

<div align="center">
    <img src="/media/class_diagram2.png" alt="그림1. 클래스 다이어그램" width="70%">
    <p>그림2. 클래스 다이어그램</p>
</div>

- GameManager에서는 상태 패턴을 사용하여 ReadyState, OpeningState 등 다양한 상태를 관리할 수 있도록 하였다.
- GameState 인터페이스를 정의하고, 구체적인 상태 클래스가 해당 인터페이스를 구현하도록 설계하여 의존성을 역전시켰다.
- 각각의 상태 클래스는 FNDController와 BuzzerController를 사용하여 게임 화면과 음악을 출력한다.

## 5. 당첨 결과 확인 알고리즘

```cpp
Letter CheckResult()
{
    vector<unsigned char> results(reels);
    std::sort(results.begin(), results.end());

    int maxSameCnt = 1, currentSameCnt = 1;
    int maxContCnt = 1, currentContCnt = 1;

    for (size_t i = 1; i < results.size(); i++)
    {
        // Check for identical consecutive values
        if (results[i] == results[i - 1])
        {
            currentSameCnt++;
            maxSameCnt = std::max(maxSameCnt, currentSameCnt);
        }
        else
        {
            currentSameCnt = 1;
        }

        // Check for consecutive increasing values
        if (results[i] - results[i - 1] == 1)
        {
            currentContCnt++;
            maxContCnt = std::max(maxContCnt, currentContCnt);
        }
        else
        {
            currentContCnt = 1;
        }
    }

    // Return the result based on the counts
    if (maxSameCnt >= 4)
        return Letter::_1ST;
    else if (maxContCnt >= 4)
        return Letter::_2ND;
    else if (maxSameCnt == 3 || maxContCnt == 3)
        return Letter::_3RD;
    else
        return Letter::FAIL;
}
```

- '1111', '7777' 과 같은 연속된 4개의 숫자가 결과일 경우 '1st', '1234'와 같은 연속된 4개의 숫자가 결과일 경우 '2nd', '1456'이나 '2555'와 같이 숫자 3개가 동일하거나 연속된 경우 '3rd', 이외의 경우 'fail'이 되도록 알고리즘을 작성하고자 하였다.
- 단, '1324'와 같이 순서가 섞여있더라도 그에 상관없이 '2nd' 및 '3rd'를 얻을 수 있도록 했다.
- 먼저 릴들의 결과를 정렬하고, 연속된 숫자 개수 및 동일한 숫자 개수를 세는 방식으로 알고리즘을 작성하였다.

## 6. 싱글톤 관리 및 의존성 주입

```cpp
// lib/manager/game_manager.cpp 코드 일부
GameManager& GameManager::GetInstance()
{
    if (!instance) instance = new GameManager();
    return *instance;
}

void GameManager::DestroyInstance()
{
    delete instance;
    instance = nullptr;
}

GameManager* GameManager::instance = nullptr;

...

// lib/manager/game_states/ready_state.cpp 코드 일부
ReadyState::ReadyState(GameManager& gm, FNDController& fnd, BuzzerController& buzzer)
    : gm(gm), fnd(fnd), buzzer(buzzer)
{ }
```

- GameManager, FixedRateUpdater, BuzzerController 등 전역적으로 사용되는 객체들을 관리하기 위해 싱글톤 패턴을 사용하였다.
- 프로그램 종료 전 DestroyInstance() 함수를 통해, 싱글톤 객체들의 자원을 명시적으로 해제하여 메모리를 관리하였다.
- GameState 타입 객체들이 싱글톤 객체와 너무 큰 결합도를 갖지 않도록, GameState 타입 객체 생성 시 각각의 싱글톤 객체를 주입받도록 설계하였다.