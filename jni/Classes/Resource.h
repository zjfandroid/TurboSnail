#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include "HudLayer.h"
#include "Hero.h"
#include "Monster.h"

enum NUM
{
	CARD_COUNT = 6,//道具数
	CARD_INFO = 99,
	BTN_CARD = 100,

	BTN_CLOSE = 200,
	BTN_SURE,
	BTN_CANCLE,
	BTN_BUY,

	LabelAtlas_SCORE,
	LabelAtlas_TIME,
	LabelAtlas_COIN,
	LabelAtlas_PRICE,

	TAG_QUESTION_TITLE = 800,
	TAG_QUESTION_ANS,
	TAG_RIGHT_ANS,
	TAG_WRONG_ANS,
	TAG_CARD_BUY,

	TAG_DARK_BG = 900,
	TAG_COUNTDOWN,
	TAG_MENU,
};

struct ImageData
{
	const char *m_strPath;
	CCPoint m_Position;
};

struct LabelAtlasData
{
	const char *charMapFile;
	int itemWidth;
	int itemHeight;
	int startCharMap;
	CCPoint m_Position;
};

struct MenuItemData
{
	const char *charMapFile; 
	const char *charMapFilePress;
	CCPoint m_Position;
};

const HudLayer::Res HudResources =
{
	"image/bg_sky.png", ccp(0, 450),
	"image/bg_landscape.png", ccp(0, 474),
	"image/bg_road.png", ccp(0, 0), 
};

const Hero::AnimData HeroImages =
{
	"anim/hero_speed%d_%02d.png", ccp(150, 350), 10, CCRectMake(0, 0, 700, 300), 1.0f / 12.0f,
	"anim/hero_speedup_%02d.png", ccp(350, 350), 10, CCRectMake(0, 0, 700, 300), 1.0f / 12.0f, 
	"anim/ans_hit_%02d.png", ccp(350, 350), 12, CCRectMake(0, 0, 300, 360), 1.0f / 12.0f, 
};

const Monster::AnimData MonsterImgs =
{
	"anim/monster%d_idle_%02d.png", ccp(800, 400), 10, CCRectMake(0, 0, 240, 240), 1.0f / 12.0f,
	"anim/monster%d_defy_%02d.png", ccp(800, 400), 15, CCRectMake(0, 0, 240, 240), 1.0f / 12.0f,
	"anim/ans_right_%02d.png", ccp(800, 400), 10, CCRectMake(0, 0, 240, 240), 1.0f / 12.0f,
};

static const char s_pBgMain[] = "image/bg_main.jpg";
static const char s_pBgPropBoard[] = "image/board_score.png";
static const char s_pBgHelpBoard[] = "image/board_help.png";
static const char s_pBgMarketBoard[] = "image/board_market.png";
static const char s_pCountDown[] = "image/%02d.png";
static const char s_pLevelUp[] = "image/level_up.png";
static const char s_pGameOver[] = "image/game_over.png";
static const char s_pBuyDisable[] = "image/btn_buy_disable.png";

//首页
static const ImageData s_pBgLogo = { "image/logo.png", ccp(640, 527.5f) }; 

//标题栏
static const ImageData s_pBgTitle = { "image/bg_title.png", ccp(640, 727.5f) }; 

//速度进度条
static const char s_pPathProgressEmpy[] = "image/progress_empy.png"; 
static const char s_pPathProgressFull[] = "image/progress_full.png"; 
static const CCPoint &s_pPointProgress = ccp(948, 63.5f);

//时间进度条
static const char s_pTimeProgressFull[] = "image/progress_time_full.png";
static const CCPoint &s_pPointTimeProgress = ccp(649.5f, 725.2f);

//题目
static const ImageData s_pBgQuestion = { "image/bg_question.png", ccp(280, 570) };
static const ccColor3B& COLOR_QUESTION = ccc3(255, 255, 255);
static const int SIZE_QUESTION_TXT = 80;//题目字体大小

//选项
static const char s_pPathBgOption[] = "image/bg_option.png"; 
static const ccColor3B& COLOR_OPTION = ccc3(0, 0, 0);
static const int SIZE_OPTION_TXT = 63;//选项字体大小

//数字
static const LabelAtlasData s_pNumTitleScore = { "image/num_title_score.png", 40, 40, '0', ccp(343, 708) };
static const LabelAtlasData s_pNumTitleTime = { "image/num_title_time.png", 60, 60, '0', ccp(590, 700) };
static const LabelAtlasData s_pNumTitleCoin = { "image/num_title_coin.png", 26, 26, '0', ccp(865, 718) };

static const ImageData s_pathTomato = { "image/tomato.png", ccp(820, 611) };
static const LabelAtlasData s_pNumScoreCoin = { "image/num_score_coin.png", 27, 27, '0', ccp(845, 601) }; 
static const LabelAtlasData s_pNumScoreYellow = { "image/num_score_yellow.png", 54, 55, '0', ccp(750, 463) };
static const LabelAtlasData s_pNumScoreGreen = { "image/num_score_green.png", 61, 59, '0', ccp(750, 358) };
static const LabelAtlasData s_pNumScoreBlue = { "image/num_score_blue.png", 46, 48, '0', ccp(598, 270) };

static const ImageData s_pathMarketTomato = { "image/tomato.png", ccp(820, 626) };
static const LabelAtlasData s_pNumMarketCoin = { "image/num_score_coin.png", 27, 27, '0', ccp(845, 616) };

//按钮
static const MenuItemData s_pMenuItemStart = { "image/btn_start.png", "image/btn_start_press.png",};
static const MenuItemData s_pMenuItemHelp = { "image/btn_help.png", "image/btn_help_press.png",};
static const MenuItemData s_pMenuItemMarket = { "image/btn_market.png", "image/btn_market_press.png",};
static const MenuItemData s_pMenuItemSound = { "image/btn_sound.png", "image/btn_sound_press.png", };
static const MenuItemData s_pMenuItemSoundDisable = { "image/btn_sound_disable.png", "image/btn_sound_disable_press.png", };

static const MenuItemData s_pMenuItemPause = { "image/btn_pause.png", "image/btn_pause_press.png", ccp(1236, 750) };
static const MenuItemData s_pMenuItemClose = { "image/btn_close.png", "image/btn_close_press.png", }; 
static const MenuItemData s_pMenuItemChart = { "image/btn_chart.png", "image/btn_chart_press.png",};
static const MenuItemData s_pMenuItemRestart = { "image/btn_restart.png", "image/btn_restart_press.png",};

static const MenuItemData s_pMenuItemBack = { "image/btn_back.png", "image/btn_back_press.png", };
static const MenuItemData s_pMenuItemHelpStart = { "image/btn_help_start.png", "image/btn_help_start_press.png", };
static const MenuItemData s_pMenuItemBuy = { "image/btn_buy.png", "image/btn_buy_press.png", };

//道具 
static const MenuItemData s_pathCard = { "image/card_%02d.png", "image/card_%02d_press.png", ccp(340, 535) };
static const char s_pathCardDisable[] = "image/card_%02d_disable.png";
static const ImageData s_pathCardbuy = { "image/card_buy.png", ccp(100, 40) };
static const ImageData s_pathCardInfo = { "image/card_%02d_info.png", ccp(640, 300) };

static const AnimationUtils::AnimationData hero_speed_up = { "anim/hero_speedup_%02d.png", ccp(350, 400), 10, CCRectMake(0, 0, 700, 300), 1.0f / 12.0f, };

//游戏帮助
static const AnimationUtils::AnimationData help_anim = { "help/help_%02d.png", ccp(640, 470), 80, CCRectMake(0, 0, 380, 240), 1.0f / 12.0f, };

//弹出提示框
static const char *g_pExitTips[] =
{
	"image/board_exit_tips.png",		//弹出温馨提示背景
	"image/btn_sure.png",			//确定
	"image/btn_sure_press.png",
	"image/btn_cancle.png",		//取消
	"image/btn_cancle_press.png",
};

static const char s_keySore[] = "score"; 
static const char s_keyCoin[] = "coin"; 
static const char s_keyCard[] = "card_%d";

#endif
