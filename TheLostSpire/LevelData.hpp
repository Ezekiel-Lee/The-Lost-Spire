#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

// 플랫폼 정의 데이터 (x, y, width, height)
struct PlatformDef
{
    float x, y, w, h;
};

// 적 정의 데이터 (시작 위치, 순찰 거리)
struct EnemyDef
{
    float x, y;
    float patrolDistance;
};

// 룬(수집품) 위치
struct RuneDef
{
    float x, y;
};

// 레벨 하나를 구성하는 모든 데이터
struct LevelData
{
    std::string        name;
    sf::Vector2f        playerSpawn;
    std::vector<PlatformDef> platforms;
    std::vector<RuneDef>     runes;
    std::vector<EnemyDef>    enemies;
};

// 5개 레벨 데이터를 만들어 반환
std::vector<LevelData> buildLevels();
