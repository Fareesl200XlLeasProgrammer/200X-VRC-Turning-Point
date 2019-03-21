#include "main.h"

#include "display/lv_conf.h"
#include "display/lvgl.h"

#include "animations.h"

int time = 1000;
void opcontrol() {
  lv_obj_t * a1 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a1, &a1);
  lv_obj_align(a1, NULL, LV_ALIGN_IN_TOP_MID, 30, 60);

  pros::delay(2000);
  lv_obj_del(a1);

  lv_obj_t * a2 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a2, &a2);
  lv_obj_align(a2, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a2);

  lv_obj_t * a3 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a3, &a3);
  lv_obj_align(a3, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a3);

  lv_obj_t * a4 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a4, &a4);
  lv_obj_align(a4, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a4);

  lv_obj_t * a5 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a5, &a5);
  lv_obj_align(a5, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a5);

  lv_obj_t * a6 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a6, &a6);
  lv_obj_align(a6, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a6);

  lv_obj_t * a7 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a7, &a7);
  lv_obj_align(a7, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a7);

  lv_obj_t * a8 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a8, &a8);
  lv_obj_align(a8, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a8);

  lv_obj_t * a9 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a9, &a9);
  lv_obj_align(a9, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a9);

  lv_obj_t * a10 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a10, &a10);
  lv_obj_align(a10, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a10);

  lv_obj_t * a11 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a11, &a11);
  lv_obj_align(a11, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a11);

  lv_obj_t * a12 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a12, &a12);
  lv_obj_align(a12, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a12);

  lv_obj_t * a13 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a13, &a13);
  lv_obj_align(a13, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a13);

  lv_obj_t * a14 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a14, &a14);
  lv_obj_align(a14, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a14);

  lv_obj_t * a15 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a15, &a15);
  lv_obj_align(a15, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a15);

  lv_obj_t * a16 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a16, &a16);
  lv_obj_align(a16, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a16);

  lv_obj_t * a17 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a17, &a17);
  lv_obj_align(a17, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a17);

  lv_obj_t * a18 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a18, &a18);
  lv_obj_align(a18, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a18);

  lv_obj_t * a19 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a19, &a19);
  lv_obj_align(a19, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a19);

  lv_obj_t * a20 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a20, &a20);
  lv_obj_align(a20, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a20);

  lv_obj_t * a21 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a21, &a21);
  lv_obj_align(a21, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a21);

  lv_obj_t * a22 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a22, &a22);
  lv_obj_align(a22, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a22);

  lv_obj_t * a23 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a23, &a23);
  lv_obj_align(a23, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a23);

  lv_obj_t * a24 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a24, &a24);
  lv_obj_align(a24, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a24);

  lv_obj_t * a25 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a25, &a25);
  lv_obj_align(a24, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a25);

  lv_obj_t * a26 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a26, &a26);
  lv_obj_align(a26, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a26);

  lv_obj_t * a27 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a27, &a27);
  lv_obj_align(a27, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a27);

  lv_obj_t * a28 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a28, &a28);
  lv_obj_align(a28, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a28);

  lv_obj_t * a29 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a29, &a29);
  lv_obj_align(a29, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a29);

  lv_obj_t * a30 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a30, &a30);
  lv_obj_align(a30, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a30);

  lv_obj_t * a31 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a31, &a31);
  lv_obj_align(a31, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a31);

  lv_obj_t * a32 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a32, &a32);
  lv_obj_align(a32, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a32);

  lv_obj_t * a33 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a33, &a33);
  lv_obj_align(a33, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a33);

  lv_obj_t * a34 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a34, &a34);
  lv_obj_align(a34, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a34);

  lv_obj_t * a35 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a35, &a35);
  lv_obj_align(a35, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a35);

  lv_obj_t * a36 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a36, &a36);
  lv_obj_align(a36, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a36);

  lv_obj_t * a37 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a37, &a37);
  lv_obj_align(a37, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a37);

  lv_obj_t * a38 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a38, &a38);
  lv_obj_align(a38, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a38);

  lv_obj_t * a39 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a39, &a39);
  lv_obj_align(a39, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a39);

  lv_obj_t * a40 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a40, &a40);
  lv_obj_align(a40, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a40);

  lv_obj_t * a41 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a41, &a41);
  lv_obj_align(a41, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a41);

  lv_obj_t * a42 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a42, &a42);
  lv_obj_align(a42, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a42);

  lv_obj_t * a43 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a43, &a43);
  lv_obj_align(a43, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a43);

  lv_obj_t * a44 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a44, &a44);
  lv_obj_align(a44, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a44);

  lv_obj_t * a45 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a45, &a45);
  lv_obj_align(a45, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a45);

  lv_obj_t * a46 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a46, &a46);
  lv_obj_align(a46, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a46);

  lv_obj_t * a47 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a47, &a47);
  lv_obj_align(a47, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a47);

  lv_obj_t * a48 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a48, &a48);
  lv_obj_align(a48, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a48);

  lv_obj_t * a49 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a49, &a49);
  lv_obj_align(a49, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a49);

  lv_obj_t * a50 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(a50, &a50);
  lv_obj_align(a50, NULL, LV_ALIGN_IN_TOP_RIGHT, 30, 60);

  pros::delay(time);
  lv_obj_del(a50);



}
