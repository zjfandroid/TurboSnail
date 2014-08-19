#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include "HudLayer.h"
#include "Hero.h"
#include "Monster.h"

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
static const char s_pBgGameOver[] = "image/bg_over.jpg";
static const char s_pGameOver[] = "image/game_over.png";
static const char s_pGameOverShadow[] = "image/game_over_shadow.png";
static const char s_pBuyDisable[] = "image/btn_buy_disable.png";
static const char s_pLoadProgressBg[] = "image/loading_progress_bg.png";
static const char s_pLoadProgressFull[] = "image/loading_progress_full.png";

//首页
static const ImageData s_pBgLogo = { "image/logo.png", ccp(640, 527.5f) }; 

//标题栏
static const ImageData s_pBgTitle = { "image/bg_title.png", ccp(640, 732.0f) }; 

//速度进度条
static const char s_pPathProgressEmpy[] = "image/progress_empy.png"; 
static const char s_pPathProgressFull[] = "image/progress_full.png"; 
static const CCPoint &s_pPointProgress = ccp(948, 63.5f);

//时间进度条
static const char s_pTimeProgressFull[] = "image/progress_time_full.png";
static const CCPoint &s_pPointTimeProgress = ccp(649.5f, 729.7f);

//题目
static const ImageData s_pBgQuestion = { "image/bg_question.png", ccp(280, 570) };
static const ccColor3B& COLOR_QUESTION = ccc3(255, 255, 255);
static const int SIZE_QUESTION_TXT = 80;//题目字体大小

//选项
static const char s_pPathBgOption[] = "image/bg_option.png"; 
static const ccColor3B& COLOR_OPTION = ccc3(0, 0, 0);
static const int SIZE_OPTION_TXT = 63;//选项字体大小

//数字
static const LabelAtlasData s_pNumTitleScore = { "image/num_title_score.png", 40, 40, '0', ccp(343, 712) };
static const LabelAtlasData s_pNumTitleTime = { "image/num_title_time.png", 60, 60, '0', ccp(590, 700) };
static const LabelAtlasData s_pNumTitleCoin = { "image/num_title_coin.png", 26, 26, '0', ccp(865, 720) };

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
//通关动画
static const AnimationUtils::AnimationData s_pGamePass = { "pass/game_pass_%02d.png", ccp(640, 400), 61, CCRectMake(0, 0, 1280, 800), 1.0f / 12.0f, };

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

//音乐音效
static const char s_musicBgMain[] = "music/bg_music_main.mp3";//游戏首页
static const char s_musicBgGame[] = "music/bg_music_game.mp3";//游戏操作界面
static const char s_musicBgGameOver[] = "music/bg_music_gameover.mp3";//游戏结束界面
static const char s_effectCountDown[] = "music/effect_count_down.mp3";//倒计时音效（3-2-1 GO！）
static const char s_effectUseItem[] = "music/effect_use_item.mp3";//使用道具蜗牛加速动画
static const char s_effectEat[] = "music/effect_eat.mp3";//游戏操作界面-答对吃掉番茄_怪物
static const char s_effectHit[] = "music/effect_hit.mp3";//游戏操作界面-答错撞到减速
static const char s_effectAnswer[] = "music/effect_answer.mp3";//游戏操作界面-点击答案答案消失
static const char s_effectLevelUp[] = "music/effect_level_up.mp3";//过关升级了
static const char s_effectTimeLess[] = "music/effect_time_less.mp3";//游戏操作界面-时间快到了
static const char s_effectGameOver[] = "music/effect_game_over.mp3";//game over
static const char s_effectGamePass[] = "music/effect_game_pass.mp3";//游戏结束界面-恭喜过关界面
static const char s_effectBuy[] = "music/effect_buy.mp3";//购买道具界面-购买道具成功道具上面打了个勾
static const char s_effectButton[] = "music/button.mp3";

#endif
