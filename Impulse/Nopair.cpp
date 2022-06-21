#include "Impulse.h"

GAME_BEGIN(NoPair);

typedef struct pos{
	int x = 0; 
	int y = 0;
	bool used = false;
}pos;

pos position[20];
int score = 0;
int	button[7] = {};
int mark[7] = {};
int dummy_mark = -1;
int dummy_mark_2 = -1;
int dummy_mark_3 = -1;

int ans_mark = -1;
int count = 0;
void setup() {
	score = 0;
	count = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			position[i + j * 4].x = ((SCREEN_WIDTH / 6) * j) + SCREEN_WIDTH / 6;
			position[i + j * 4].y = (140 * i) + 200;
		}
	}
	stopwatch(STOPWATCH::START);
	
}

void update() {
	if (count <= 2)
	{
		if (button[0] == NULL)
		{
			create_button(3);
		}
		else {
			loop_stage_check(3);
		}
	}
	else if (count >= 3 && count <= 3) {
		if (button[3] == NULL)
		{
			//destory_all_asset(3);
			create_button(5);
		}
		else {
			loop_stage_check(5);
		}
	}else if (count >= 4 && count <= 4) {
		if (button[3] == NULL)
		{
			//destory_all_asset(3);
			create_button(7);
		}
		else {
			loop_stage_check(7);
		}
	}
	if (score >= 5)
	{
		stopwatch(STOPWATCH::STOP);
		finish();
	}
}

void reset_all_pos() {
	for (int i = 0; i < 20; i++)
	{
		position[i].used = false;
	}
}
void change_posi(int num) {
	reset_all_pos();
	ans_mark = random_ans();
	dummy_mark = random_not_ans(ans_mark);
	
	for (int i = 0; i < num; i++)
	{
		int random_pos = random_position_not_use(position);

		
		setAsset(button[i], CMD::POS_X, position[random_pos].x);
		setAsset(button[i], CMD::POS_Y, position[random_pos].y);

		
		setAsset(mark[i], CMD::POS_X, position[random_pos].x);
		setAsset(mark[i], CMD::POS_Y, position[random_pos].y);
		if (i == 1)
		{
			setAsset(mark[i], CMD::STATUS, ans_mark);

		}
		else {
			setAsset(mark[i], CMD::STATUS, dummy_mark);

		}
		position[random_pos].used = true;

	}
}
void loop_stage_check(int num) {
	for (int i = 0; i < num; i++)
	{
		int t = getAsset(button[i], CMD:: TOUCH);
		if (getAsset(mark[i],CMD::STATUS) == ans_mark && t)
		{
			count++;
			if (count <= num)
			{
				change_posi(num);
			}
			destory_all_asset(num);
			returnToNull(num);
			score++;
		}
	}
}
int random_position_not_use(pos target[]) {
	int num = -1;
	do {
		num = random() % 20;
		/*if (target[num].used == false)
		{
			break;
		}*/
	} while (target[num].used == true);
	return num;
}
void create_button(int button_size) {
	ans_mark = random_ans();
	dummy_mark = random_not_ans(ans_mark);
	dummy_mark_2 = random_not_ans(ans_mark, dummy_mark);
	dummy_mark_3 = random_not_ans(ans_mark, dummy_mark,dummy_mark_2);
	for (int i = 0; i < button_size; i++)
	{
		int random_pos = random_position_not_use(position);

		button[i] = createAsset(ASSET::BUTTON);
		setAsset(button[i], CMD::POS_X, position[random_pos].x);
		setAsset(button[i], CMD::POS_Y, position[random_pos].y);
		
		mark[i] = createAsset(ASSET::MARK);
		setAsset(mark[i], CMD::POS_X, position[random_pos].x);
		setAsset(mark[i], CMD::POS_Y, position[random_pos].y);
		if (i == 1)
		{
			setAsset(mark[i], CMD::STATUS, ans_mark);

		}
		else if (i <= 2) {
			setAsset(mark[i], CMD::STATUS, dummy_mark);

		}
		else if (i <= 4){
			setAsset(mark[i], CMD::STATUS, dummy_mark_2);

		}
		else {
			setAsset(mark[i], CMD::STATUS, dummy_mark_3);

		}
		
		position[random_pos].used = true;
	}
}
int random_ans() {
	int ans = CN_MARK_DRINK + (random() % 4);
	return ans;
}
int random_not_ans(int ans,int not_dummy = -1, int not_dummy_2 = -1) {
	int dummy = -1;
	do {
		dummy = CN_MARK_DRINK +(random() % 4);
		
	} while (dummy == ans || dummy == not_dummy || dummy == not_dummy_2);
	return dummy;
}

void destory_all_asset(int num) {
	for (int i = 0; i < num; i++)
	{
		destroyAsset(mark[i]);
		destroyAsset(button[i]);
	}
}

void returnToNull(int num) {
	for (int i = 0; i < num; i++)
	{
		button[i] = NULL;
	}
}
GAME_END;