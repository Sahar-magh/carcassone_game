#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../structure/carte.h"
#include "../structure/link.h"
#include "../updateFunctions/updateTown.h"

////////////Function used to debug////////////

void aff_tuile(struct tuille t){
  printf("----------tuile-------------\n");
  printf("type : { ");
  for(int i =0;i<4;i++){
    printf("{ ");
    for(int j=0;j<3;j++){
      printf("%d, ",t.type[i][j]);
    }
    printf("} ");
  }
  printf("}\n");
  printf("pion : { ");
  for(int i =0;i<4;i++){
    printf("{ ");
    for(int j=0;j<3;j++){
      printf("%d, ",t.pion[i][j]);
    }
    printf("} ");
  }
  printf("}\n");
  printf("id : %d\n",t.id);
  printf("dir : %d\n",t.dir);
  printf("milieu : %d\n",t.milieu);
  printf("shield : %d\n",t.shield);
  printf("position : (%d,%d)\n",t.position[0],t.position[1]);
  printf("---------------------------\n");
  printf("\n");
}

//////////////////////////////////////////////

/////////////////TESTS////////////////////////

void test_FieldVide(){
  struct field * test_field = FieldVide();
  struct tuille * test_tuille = (struct tuille * )test_field->lst_tutuille->head->data;
  assert(test_field->lst_triplet->head == NULL);
  struct tuille tvide = gen_tuile_vide();
  for (int i = 0;i<PLAYER_MAX;i++){
    assert(test_field->paysans[i] == 0);
  }
  assert(test_field->len == NONE);
  assert(same_card(&tvide,test_tuille) == TRUE);
  
  printf("TEST_FIELD_VIDE\t\t\t:");
  printf("\x1b[32m" "\tCHECK\n" "\x1b[0m");
}





void test_TownVide(){
  struct city * test_town = TownVide();
  struct tuille * test_tuille = (struct tuille * )test_town->lst_tutuille->head->data;
  assert(test_town->lst_champ->head == NULL);
  struct triplet * test_triplet = (struct triplet * )test_town->lst_triplet->head->data;

  assert(test_triplet->x == NONE);
  assert(test_triplet->y == NONE);
  assert(test_triplet->z == NONE);
  
  struct tuille tvide = gen_tuile_vide();
  
  assert(same_card(&tvide,test_tuille) == TRUE);
  
  for (int i = 0;i<PLAYER_MAX;i++){
    assert(test_town->chevaliers[i] == 0);
  }
  assert(test_town->len == NONE);
  assert(test_town->shield == NONE);
  assert(test_town->border == NONE);
  
  printf("TEST_TOWN_VIDE\t\t\t:");
  printf("\x1b[32m" "\tCHECK\n" "\x1b[0m");
}







void test_ExtractTown(){
  //init phase//
  struct tuille tvide = gen_tuile_vide();
  struct city * test_town_1[4];
  struct city * test_town_2[4];
  struct city * test_town_3[4];
  struct city * test_town_4[4];
  for(int i = 0;i<4;i++){
    test_town_1[i] = TownVide();
    test_town_2[i] = TownVide();
    test_town_3[i] = TownVide();
    test_town_4[i] = TownVide();
  } 
  struct tuille center_town = genere_tuille(6);
  struct tuille double_corner_town = genere_tuille(23);
  struct tuille corner_town = genere_tuille(34);
  struct tuille single_town = genere_tuille(15);
  center_town.position[0] = 10;
  center_town.position[1] = 10;
  double_corner_town.position[0] = 20;
  double_corner_town.position[1] = 20;
  corner_town.position[0] = 30;
  corner_town.position[1] = 30;
  single_town.position[0] = 40;
  single_town.position[1] = 40;
  

  //center town tests//
  assert(ExtractTown(&center_town,test_town_1) == 4);
  struct lelement * llm_tutuille_town = llm_empty();
  struct lelement * llm_triplet_town = llm_empty();
  struct tuille * test_tuille;
  struct triplet * test_triplet;
  for (int i = 0;i<4;i++){
    llm_tutuille_town = test_town_1[i]->lst_tutuille->head;
    llm_triplet_town = test_town_1[i]->lst_triplet->head;
    test_tuille = (struct tuille * )llm_tutuille_town->data;
    test_triplet = (struct triplet * )llm_triplet_town->data;
    assert(same_card(test_tuille,&center_town) == TRUE);
    assert(test_triplet->x == 10);
    assert(test_triplet->y == 10);
    assert(test_triplet->z == attribut_z_town(i));
    assert(llm_tutuille_town->next == NULL);
    assert(llm_triplet_town->next == NULL);
  }

  //double corner town tests//
  assert(ExtractTown(&double_corner_town,test_town_2) == 2);
  for (int i = 0;i<2;i++){
    llm_tutuille_town = test_town_2[i]->lst_tutuille->head;
    llm_triplet_town = test_town_2[i]->lst_triplet->head;
    test_tuille = (struct tuille * )llm_tutuille_town->data;
    test_triplet = (struct triplet * )llm_triplet_town->data;
    assert(same_card(test_tuille,&double_corner_town) == TRUE);
    assert(test_triplet->x == 20);
    assert(test_triplet->y == 20);
    assert(test_triplet->z == attribut_z_town(i+2));
    assert(llm_tutuille_town->next == NULL);
    assert(llm_triplet_town->next == NULL);
  }
  for (int i = 2;i<4;i++){
    llm_tutuille_town = test_town_2[i]->lst_tutuille->head;
    llm_triplet_town = test_town_2[i]->lst_triplet->head;
    test_tuille = (struct tuille * )llm_tutuille_town->data;
    test_triplet = (struct triplet * )llm_triplet_town->data;
    assert(same_card(&tvide,test_tuille) == TRUE);
    assert(test_triplet->x == NONE);
    assert(test_triplet->y == NONE);
    assert(test_triplet->z == NONE);
    assert(llm_tutuille_town->next == NULL);
    assert(llm_triplet_town->next == NULL);
  }

  //corner town tests//
  assert(ExtractTown(&corner_town,test_town_3) == 2);
  for (int i = 0;i<2;i++){
    llm_tutuille_town = test_town_3[i]->lst_tutuille->head;
    llm_triplet_town = test_town_3[i]->lst_triplet->head;
    test_tuille = (struct tuille * )llm_tutuille_town->data;
    test_triplet = (struct triplet * )llm_triplet_town->data;
    assert(same_card(test_tuille,&corner_town) == TRUE);
    assert(test_triplet->x == 30);
    assert(test_triplet->y == 30);
    assert(test_triplet->z == attribut_z_town(i));
    assert(llm_tutuille_town->next == NULL);
    assert(llm_triplet_town->next == NULL);
  }
  for (int i = 2;i<4;i++){
    llm_tutuille_town = test_town_3[i]->lst_tutuille->head;
    llm_triplet_town = test_town_3[i]->lst_triplet->head;
    test_tuille = (struct tuille * )llm_tutuille_town->data;
    test_triplet = (struct triplet * )llm_triplet_town->data;
    assert(same_card(&tvide,test_tuille) == TRUE);
    assert(test_triplet->x == NONE);
    assert(test_triplet->y == NONE);
    assert(test_triplet->z == NONE);
    assert(llm_tutuille_town->next == NULL);
    assert(llm_triplet_town->next == NULL);
  }

  //single town tests//
  assert(ExtractTown(&single_town,test_town_4) == 1);
  for (int i = 0;i<1;i++){
    llm_tutuille_town = test_town_4[i]->lst_tutuille->head;
    llm_triplet_town = test_town_4[i]->lst_triplet->head;
    test_tuille = (struct tuille * )llm_tutuille_town->data;
    test_triplet = (struct triplet * )llm_triplet_town->data;
    assert(same_card(test_tuille,&single_town) == TRUE);
    assert(test_triplet->x == 40);
    assert(test_triplet->y == 40);
    assert(test_triplet->z == attribut_z_town(i));
    assert(llm_tutuille_town->next == NULL);
    assert(llm_triplet_town->next == NULL);
  }
  for (int i = 1;i<4;i++){
    llm_tutuille_town = test_town_4[i]->lst_tutuille->head;
    llm_triplet_town = test_town_4[i]->lst_triplet->head;
    test_tuille = (struct tuille * )llm_tutuille_town->data;
    test_triplet = (struct triplet * )llm_triplet_town->data;
    assert(same_card(&tvide,test_tuille) == TRUE);
    assert(test_triplet->x == NONE);
    assert(test_triplet->y == NONE);
    assert(test_triplet->z == NONE);
    assert(llm_tutuille_town->next == NULL);
    assert(llm_triplet_town->next == NULL);
  }  
  
  printf("TEST_EXTRACT_TOWN\t\t:"); 
  printf("\x1b[32m" "\tCHECK\n" "\x1b[0m"); 
}







void test_SingleTripletField(){
  //init phase//
  struct tuille segment_road_town_1 = genere_tuille(10);
  struct tuille crossroad_road_town = genere_tuille(32);
  struct tuille segment_road_town_2 = genere_tuille(26);
  struct field * field_segment_1 = FieldVide();
  struct field * field_crossroad = FieldVide();
  struct field * field_segment_2 = FieldVide();
  
  segment_road_town_1.position[0] = 10;
  segment_road_town_1.position[1] = 10;
  crossroad_road_town.position[0] = 20;
  crossroad_road_town.position[1] = 20;
  segment_road_town_2.position[0] = 30;
  segment_road_town_2.position[1] = 30;
  
  struct lelement * llm_segment_1 = llm_empty();
  struct lelement * llm_crossroad = llm_empty();
  struct lelement * llm_segment_2 = llm_empty();
  llm_segment_1->data = &segment_road_town_1;
  llm_crossroad->data = &crossroad_road_town;
  llm_segment_2->data = &segment_road_town_2;
  
  lnk_add2(field_segment_1->lst_tutuille,llm_segment_1);
  lnk_add2(field_crossroad->lst_tutuille,llm_crossroad);
  lnk_add2(field_segment_2->lst_tutuille,llm_segment_2);

  //segment case//
  SingleTripletField(segment_road_town_1,field_segment_1);

  struct lelement * llm_triplet = llm_empty();
  struct triplet * test_triplet;
  llm_triplet = field_segment_1->lst_triplet->head;
  test_triplet = (struct triplet * )llm_triplet->data;
  assert(test_triplet->x == 10);
  assert(test_triplet->y == 10);
  assert(test_triplet->z == 0);
  test_triplet = (struct triplet * )llm_triplet->next->data;
  assert(test_triplet->x == 10);
  assert(test_triplet->y == 10);
  assert(test_triplet->z == 8);
  assert(llm_triplet->next->next == NULL);
  
  //crossroad case//
  SingleTripletField(crossroad_road_town,field_crossroad);


  llm_triplet = field_crossroad->lst_triplet->head;
  test_triplet = (struct triplet * )llm_triplet->data;
  assert(test_triplet->x == 20);
  assert(test_triplet->y == 20);
  assert(test_triplet->z == 0);
  test_triplet = (struct triplet * )llm_triplet->next->data;
  assert(test_triplet->x == 20);
  assert(test_triplet->y == 20);
  assert(test_triplet->z == 8);
  assert(llm_triplet->next->next == NULL);


  //curved segment case//
  SingleTripletField(segment_road_town_2,field_segment_2);

  llm_triplet = field_segment_2->lst_triplet->head;
  for(int i = 0;i<9;i++){
    if ((i > 7) || (i < 4)){
      test_triplet = (struct triplet * )llm_triplet->data;
      assert(test_triplet->x == 30);
      assert(test_triplet->y == 30);
      assert(test_triplet->z == i+3);
      llm_triplet = llm_triplet->next;
    }
  }
  assert(llm_triplet == NULL);  
  
  
  printf("TEST_SINGLE_TRIPLET_FIELD\t:");
  printf("\x1b[32m" "\tCHECK\n" "\x1b[0m");
}








void test_PluralFieldDouble(){
  //init phase//
  struct tuille bridge_town = genere_tuille(18); 
  struct tuille bridge_s_town = genere_tuille(17);
  struct tuille corner_full = genere_tuille(34);
  struct tuille corner_full_road = genere_tuille(39);
  struct tuille unlinked_d = genere_tuille(21);
  struct tuille unlinked_d_c = genere_tuille(23);

  struct city * town_1 = TownVide();
  struct city * town_2 = TownVide();
  struct city * town_3 = TownVide();
  struct city * town_4 = TownVide();
  struct city * town_5 = TownVide();
  struct city * town_6 = TownVide();

  bridge_town.position[0] = 10;
  bridge_town.position[1] = 10;
  bridge_s_town.position[0] = 20;
  bridge_s_town.position[1] = 20;
  corner_full.position[0] = 30;
  corner_full.position[1] = 30;
  corner_full_road.position[0] = 40;
  corner_full_road.position[1] = 40;
  unlinked_d.position[0] = 50;
  unlinked_d.position[1] = 50;
  unlinked_d_c.position[0] = 60;
  unlinked_d_c.position[1] = 60;

  struct lelement * llm_bridge = llm_empty();
  struct lelement * llm_bridge_s = llm_empty();
  struct lelement * llm_cor_f = llm_empty();
  struct lelement * llm_cor_f_r = llm_empty();
  struct lelement * llm_unl_d = llm_empty();
  struct lelement * llm_unl_d_c = llm_empty();

  struct triplet bridge_triplet_1 = {10,10,1};
  struct triplet bridge_triplet_2 = {10,10,7};
  struct triplet bridge_s_triplet_1 = {20,20,3};
  struct triplet bridge_s_triplet_2 = {20,20,5};
  struct triplet corner_triplet_1 = {30,30,1};
  struct triplet corner_triplet_2 = {30,30,3};
  struct triplet corner_r_triplet_1 = {40,40,1};
  struct triplet corner_r_triplet_2 = {40,40,3};
  struct triplet unlinked_triplet_1 = {50,50,3};
  struct triplet unlinked_triplet_2 = {50,50,5};
  struct triplet unlinked_c_triplet_1 = {60,60,7};
  struct triplet unlinked_c_triplet_2 = {60,60,5};

  struct lelement * llm_1 = llm_empty();
  struct lelement * llm_2 = llm_empty();
  struct lelement * llm_3 = llm_empty();
  struct lelement * llm_4 = llm_empty();
  struct lelement * llm_5 = llm_empty();
  struct lelement * llm_6 = llm_empty();
  struct lelement * llm_7 = llm_empty();
  struct lelement * llm_8 = llm_empty();
  struct lelement * llm_9 = llm_empty();
  struct lelement * llm_10 = llm_empty();
  struct lelement * llm_11 = llm_empty();
  struct lelement * llm_12 = llm_empty();

  llm_1->data = &bridge_triplet_1;
  llm_2->data = &bridge_triplet_2;
  llm_3->data = &bridge_s_triplet_1;
  llm_4->data = &bridge_s_triplet_2;
  llm_5->data = &corner_triplet_1;
  llm_6->data = &corner_triplet_2;
  llm_7->data = &corner_r_triplet_1;
  llm_8->data = &corner_r_triplet_2;
  llm_9->data = &unlinked_triplet_1;
  llm_10->data = &unlinked_triplet_2;
  llm_11->data = &unlinked_c_triplet_1;
  llm_12->data = &unlinked_c_triplet_2;

  town_1->lst_triplet->head = llm_1;
  town_1->lst_triplet->tail = llm_1;
  lnk_add2(town_1->lst_triplet,llm_2);
  town_2->lst_triplet->head = llm_3;
  town_2->lst_triplet->tail = llm_3;
  lnk_add2(town_2->lst_triplet,llm_4);
  town_3->lst_triplet->head = llm_5;
  town_3->lst_triplet->tail = llm_5;
  lnk_add2(town_3->lst_triplet,llm_6);
  town_4->lst_triplet->head = llm_7;
  town_4->lst_triplet->tail = llm_7;
  lnk_add2(town_4->lst_triplet,llm_8);
  town_5->lst_triplet->head = llm_9;
  town_5->lst_triplet->tail = llm_9;
  lnk_add2(town_5->lst_triplet,llm_10);
  town_6->lst_triplet->head = llm_11;
  town_6->lst_triplet->tail = llm_11;
  lnk_add2(town_6->lst_triplet,llm_12);

  town_1->border = 2;
  town_2->border = 2;
  town_3->border = 2;
  town_4->border = 2;
  
  llm_bridge->data = &bridge_town;
  llm_bridge_s->data = &bridge_s_town;
  llm_cor_f->data = &corner_full;
  llm_cor_f_r->data = &corner_full_road;
  llm_unl_d->data = &unlinked_d;
  llm_unl_d_c->data = &unlinked_d_c;

  lnk_add2(town_1->lst_tutuille,llm_bridge);
  lnk_add2(town_2->lst_tutuille,llm_bridge_s);
  lnk_add2(town_3->lst_tutuille,llm_cor_f);
  lnk_add2(town_4->lst_tutuille,llm_cor_f_r);
  lnk_add2(town_5->lst_tutuille,llm_unl_d);
  lnk_add2(town_6->lst_tutuille,llm_unl_d_c);

  struct lelement * llm_field = llm_empty();
  struct field * test_field;
  struct tuille * test_tuille;
  struct lelement * llm_triplet;
  struct triplet * test_triplet;

  //bridge without shield case//
  PluralFieldDouble(town_1,bridge_town);

  llm_field = town_1->lst_champ->head;  
  for(int i = 0;i<2;i++){
    test_field = (struct field * )llm_field->data;
    test_tuille = (struct tuille * )test_field->lst_tutuille->head->data;
    assert(same_card(test_tuille,&bridge_town) == TRUE);
    llm_triplet = test_field->lst_triplet->head;
    for(int j = 0;j<3;j++){
      test_triplet = (struct triplet * )llm_triplet->data;
      assert(test_triplet->x == 10);
      assert(test_triplet->y == 10);
      assert(test_triplet->z == j+i*6+3);
      if(j < 2){
	llm_triplet = llm_triplet->next;
      }
    }
    llm_field = llm_field->next;
  }
  assert(llm_field == NULL);

  //bridge with shield case//
  PluralFieldDouble(town_2,bridge_s_town);

  llm_field = town_2->lst_champ->head;  
  for(int i = 0;i<2;i++){
    test_field = (struct field * )llm_field->data;
    test_tuille = (struct tuille * )test_field->lst_tutuille->head->data;
    assert(same_card(test_tuille,&bridge_s_town) == TRUE);
    llm_triplet = test_field->lst_triplet->head;
    for(int j = 0;j<3;j++){
      test_triplet = (struct triplet * )llm_triplet->data;
      assert(test_triplet->x == 20);
      assert(test_triplet->y == 20);
      assert(test_triplet->z == j+i*6);
      if(j<2){
	llm_triplet = llm_triplet->next;
      }
    }
    llm_field = llm_field->next;
  }
  assert(llm_field == NULL);

  //corner case//
  PluralFieldDouble(town_3,corner_full);

  llm_field = town_3->lst_champ->head;
  for(int i = 0;i<1;i++){
    test_field = (struct field * )llm_field->data;
    test_tuille = (struct tuille * )test_field->lst_tutuille->head->data;
    assert(same_card(test_tuille,&corner_full) == TRUE);
    llm_triplet = test_field->lst_triplet->head;
    for(int j = 0;j<6;j++){
      test_triplet = (struct triplet * )llm_triplet->data;
      assert(test_triplet->x == 30);
      assert(test_triplet->y == 30);
      assert(test_triplet->z == j+i*3+6);
      if(j < 5){
	llm_triplet = llm_triplet->next;
      }
    }
    llm_field = llm_field->next;
  }
  assert(llm_field == NULL);
 
  //corner case//
  PluralFieldDouble(town_4,corner_full_road);

  llm_field = town_4->lst_champ->head;
  for(int i = 0;i<1;i++){
    test_field = (struct field * )llm_field->data;
    test_tuille = (struct tuille * )test_field->lst_tutuille->head->data;
    assert(same_card(test_tuille,&corner_full_road) == TRUE);
    llm_triplet = test_field->lst_triplet->head;
    for(int j = 0;j<1;j++){
      test_triplet = (struct triplet * )llm_triplet->data;
      assert(test_triplet->x == 40);
      assert(test_triplet->y == 40);
      assert(test_triplet->z == j+i*3+6);
      if(j < 0){
	llm_triplet = llm_triplet->next;
      }
    }
    llm_field = llm_field->next;
  }
  assert(llm_field == NULL);

  //unlinked parallel case//
  PluralFieldDouble(town_5,unlinked_d);

  llm_field = town_5->lst_champ->head;
  for(int i = 0;i<1;i++){
    test_field = (struct field * )llm_field->data;
    test_tuille = (struct tuille * )test_field->lst_tutuille->head->data;
    assert(same_card(test_tuille,&unlinked_d) == TRUE);
    llm_triplet = test_field->lst_triplet->head;
    for(int j = 0;j<3;j++){
      test_triplet = (struct triplet * )llm_triplet->data;
      assert(test_triplet->x == 50);
      assert(test_triplet->y == 50);
      assert(test_triplet->z == j+i*6);
      if(j < 2){
	llm_triplet = llm_triplet->next;
      }
    }
    llm_field = llm_field->next;
  }
  assert(llm_field == NULL);

  //unlinked corner case//
  PluralFieldDouble(town_6,unlinked_d_c);

  llm_field = town_6->lst_champ->head;
  for(int i = 0;i<1;i++){
    test_field = (struct field * )llm_field->data;
    test_tuille = (struct tuille * )test_field->lst_tutuille->head->data;
    assert(same_card(test_tuille,&unlinked_d_c) == TRUE);
    llm_triplet = test_field->lst_triplet->head;
    for(int j = 0;j<6;j++){
      test_triplet = (struct triplet * )llm_triplet->data;
      assert(test_triplet->x == 60);
      assert(test_triplet->y == 60);
      assert(test_triplet->z == j);
      if(j < 5){
	llm_triplet = llm_triplet->next;
      }
    }
    llm_field = llm_field->next;
  }
  assert(llm_field == NULL);
  


  printf("TEST_PLURAL_FIELD_DOUBLE\t:");
  printf("\x1b[32m" "\tCHECK\n" "\x1b[0m");
}









void test_PluralFieldTriple(){
  //init phase//
  struct tuille entry_town = genere_tuille(46);
  struct tuille entry_road_town = genere_tuille(49);
  struct lelement * llm_entry = llm_empty();
  struct lelement * llm_r_entry = llm_empty();
  struct city * town_1 = TownVide();
  struct city * town_2 = TownVide();
  struct triplet entry_triplet_1 = {10,10,1};
  struct triplet entry_triplet_2 = {10,10,3};
  struct triplet entry_triplet_3 = {10,10,5};
  struct triplet entry_road_triplet_1 = {20,20,1};
  struct triplet entry_road_triplet_2 = {20,20,3};
  struct triplet entry_road_triplet_3 = {20,20,5};
  struct lelement * llm_1 = llm_empty();
  struct lelement * llm_2 = llm_empty();
  struct lelement * llm_3 = llm_empty();
  struct lelement * llm_4 = llm_empty();
  struct lelement * llm_5 = llm_empty();
  struct lelement * llm_6 = llm_empty();

  entry_town.position[0] = 10;
  entry_town.position[1] = 10;
  entry_road_town.position[0] = 20;
  entry_road_town.position[1] = 20;
  
  llm_1->data = &entry_triplet_1;
  llm_2->data = &entry_triplet_2;
  llm_3->data = &entry_triplet_3;
  llm_4->data = &entry_road_triplet_1;
  llm_5->data = &entry_road_triplet_2;
  llm_6->data = &entry_road_triplet_3;

  town_1->lst_triplet->head = llm_1;
  town_1->lst_triplet->tail = llm_1;
  lnk_add2(town_1->lst_triplet,llm_2);
  lnk_add2(town_1->lst_triplet,llm_3);
  town_2->lst_triplet->head = llm_4;
  town_2->lst_triplet->tail = llm_4;
  lnk_add2(town_2->lst_triplet,llm_5);
  lnk_add2(town_2->lst_triplet,llm_6);
  
  llm_entry->data = &entry_town;
  llm_r_entry->data = &entry_road_town;
  lnk_add2(town_1->lst_tutuille,llm_entry);
  lnk_add2(town_2->lst_tutuille,llm_r_entry);

  //entry case//
  PluralFieldTriple(town_1,entry_town);

  struct lelement * llm_field = llm_empty();
  struct field * test_field;
  struct tuille * test_tuille;
  struct lelement * llm_triplet;
  struct triplet * test_triplet;

  llm_field = town_1->lst_champ->head;
  test_field = (struct field * )llm_field->data;
  test_tuille = (struct tuille * )test_field->lst_tutuille->head->data;
  assert(same_card(test_tuille,&entry_town) == TRUE);
  llm_triplet = test_field->lst_triplet->head;
  for(int j = 0;j<3;j++){
    test_triplet = (struct triplet * )llm_triplet->data;
    assert(test_triplet->x == 10);
    assert(test_triplet->y == 10);
    assert(test_triplet->z == 6+j);
    if(j < 2){
      llm_triplet = llm_triplet->next;
    }
  }

  //entry road case//
  PluralFieldTriple(town_2,entry_road_town);

  llm_field = town_2->lst_champ->head;
  for(int i = 0;i<2;i++){
    test_field = (struct field * )llm_field->data;
    test_tuille = (struct tuille * )test_field->lst_tutuille->head->data;
    assert(same_card(test_tuille,&entry_road_town) == TRUE);
    llm_triplet = test_field->lst_triplet->head;
    test_triplet = (struct triplet * )llm_triplet->data;
    assert(test_triplet->x == 20);
    assert(test_triplet->y == 20);
    assert(test_triplet->z == 6 + i*2);
    llm_field = llm_field->next;
  }
  assert(llm_field == NULL);

  printf("TEST_PLURAL_FIELD_TRIPLE\t:");
  printf("\x1b[32m" "\tCHECK\n" "\x1b[0m");
}






void test_InternFusionTown(){ 
  //init phase//
  struct tuille unlinked_d_c = genere_tuille(23);
  struct tuille corner_full_road = genere_tuille(39);

  unlinked_d_c.position[0] = 10;
  unlinked_d_c.position[1] = 10;
  unlinked_d_c.pion[0][1] = 1;
  corner_full_road.position[0] = 20;
  corner_full_road.position[1] = 20;
  corner_full_road.pion[0][1] = 2;

  struct city * town_1[4];
  struct city * town_2[4];
  for(int i = 0;i<4;i++){
    town_1[i] = TownVide();
    town_2[i] = TownVide();
  }

  ExtractTown(&unlinked_d_c,town_1);
  ExtractTown(&corner_full_road,town_2);

  struct lelement * llm_field = llm_empty();
  struct field * test_field;
  struct tuille * test_tuille_f;
  struct lelement * llm_triplet_f;
  struct triplet * test_triplet_f;  

  struct tuille * test_tuille_t;
  struct lelement * llm_triplet_t;
  struct triplet * test_triplet_t;

  //unlinked corner case//
  assert(InternFusionTown(unlinked_d_c,town_1,2) == 2);
  
  for(int i = 0;i<2;i++){
    test_tuille_t = (struct tuille * )town_1[i]->lst_tutuille->head->data;
    assert(same_card(test_tuille_t,&unlinked_d_c) == TRUE);
    llm_triplet_t = town_1[i]->lst_triplet->head;
    for(int j = 0;j<1;j++){
      test_triplet_t = (struct triplet * )llm_triplet_t->data;
      assert(test_triplet_t->x == 10);
      assert(test_triplet_t->y == 10);
      assert(test_triplet_t->z == 7 - i*2);
      if(j < 0){
	llm_triplet_t = llm_triplet_t->next;
      }
    }
    llm_field = town_1[i]->lst_champ->head;
    for(int j = 0;j<1;j++){
      test_field = (struct field * )llm_field->data;
      test_tuille_f = (struct tuille * )test_field->lst_tutuille->head->data;
      assert(same_card(test_tuille_f,&unlinked_d_c) == TRUE);
      llm_triplet_f = test_field->lst_triplet->head;
      for(int k = 0;k<6;k++){
	test_triplet_f = (struct triplet * )llm_triplet_f->data;
	assert(test_triplet_f->x == 10);
	assert(test_triplet_f->y == 10);
	assert(test_triplet_f->z == k);
	if(k < 5){
	  llm_triplet_f = llm_triplet_f->next;
	}
      }
      llm_field = llm_field->next;
    }
    assert(llm_field == NULL);
  }

  //no single town case//
  assert(InternFusionTown(corner_full_road,town_2,2) == 1);
  
  for(int i = 0;i<1;i++){
    test_tuille_t = (struct tuille * )town_2[i]->lst_tutuille->head->data;
    assert(same_card(test_tuille_t,&corner_full_road) == TRUE);
    llm_triplet_t = town_2[i]->lst_triplet->head;
    for(int j = 0;j<2;j++){
      test_triplet_t = (struct triplet * )llm_triplet_t->data;
      assert(test_triplet_t->x == 20);
      assert(test_triplet_t->y == 20);
      assert(test_triplet_t->z == 1+j*2);
      if(j < 1){
	llm_triplet_t = llm_triplet_t->next;
      }
    }
    llm_field = town_2[i]->lst_champ->head;
    for(int j = 0;j<1;j++){
      test_field = (struct field * )llm_field->data;
      test_tuille_f = (struct tuille * )test_field->lst_tutuille->head->data;
      assert(same_card(test_tuille_f,&corner_full_road) == TRUE);
      llm_triplet_f = test_field->lst_triplet->head;
      for(int k = 0;k<2;k++){
	test_triplet_f = (struct triplet * )llm_triplet_f->data;
	assert(test_triplet_f->x == 20);
	assert(test_triplet_f->y == 20);
	assert(test_triplet_f->z == 6+k*5);
	if(k < 1){
	  llm_triplet_f = llm_triplet_f->next;
	}
      }
      llm_field = llm_field->next;
    }
    assert(llm_field == NULL);
  }

     
  printf("TEST_INTER_FUSION_TOWN\t\t:");
  printf("\x1b[32m" "\tCHECK\n" "\x1b[0m");
}





void test_MergeTown(){
  //init phase//
  struct city * town_1 = TownVide();
  struct city * town_2 = TownVide();
  struct city * town_3 = TownVide();

  struct city * trans_town_1[4];
  struct city * trans_town_2[4];
  struct city * trans_town_3[4];

  for(int i = 0;i<4;i++){
    trans_town_1[i] = TownVide();
    trans_town_2[i] = TownVide();
    trans_town_3[i] = TownVide();
  }

  struct tuille tutuille_1 = genere_tuille(6);
  struct tuille tutuille_2 = genere_tuille(48);
  struct tuille tutuille_3 = genere_tuille(10);
  
  tutuille_1.position[0] = 10;
  tutuille_1.position[1] = 10;
  tutuille_2.position[0] = 11;
  tutuille_2.position[1] = 10;
  tutuille_3.position[0] = 10;
  tutuille_3.position[1] = 9;
  tutuille_1.pion[0][1] = 1;

  int num1 = ExtractTown(&tutuille_1,trans_town_1);
  int num2 = ExtractTown(&tutuille_2,trans_town_2);
  int num3 = ExtractTown(&tutuille_3,trans_town_3);

  InternFusionTown(tutuille_1,trans_town_1,num1);
  InternFusionTown(tutuille_2,trans_town_2,num2);
  InternFusionTown(tutuille_3,trans_town_3,num3);

  town_1 = trans_town_1[0];
  town_2 = trans_town_2[0];
  town_3 = trans_town_3[0];

  struct lelement * llm_tuille;
  struct tuille * test_tuille;
  struct lelement * llm_field;
  struct field * test_field;
  struct lelement * llm_triplet;
  struct triplet * test_triplet;

  //1 v 1 case//
  MergeTown(town_1,town_2);

  llm_field = town_1->lst_champ->head;
  
  llm_tuille = town_1->lst_tutuille->head;
  test_tuille = (struct tuille * )llm_tuille->data;
  assert(same_card(test_tuille,&tutuille_1) == TRUE); 
  llm_tuille = llm_tuille->next;
  test_tuille = (struct tuille * )llm_tuille->data;
  assert(same_card(test_tuille,&tutuille_2) == TRUE);

  llm_triplet = town_1->lst_triplet->head;
  for(int i = 0;i<4;i++){
    test_triplet = (struct triplet * )llm_triplet->data;
    assert(test_triplet->x == 10);
    assert(test_triplet->y == 10);
    if(i > 1){
      assert(test_triplet->z == 7 - 2*(i-2));
    }
    else{
      assert(test_triplet->z == 1+2*i);
    }
    llm_triplet = llm_triplet->next;
  }
  for(int i = 0;i<3;i++){
    test_triplet = (struct triplet * )llm_triplet->data;
    assert(test_triplet->x == 11);
    assert(test_triplet->y == 10);
    if(i == 2){
      assert(test_triplet->z == 5);
    }
    else {
      assert(test_triplet->z == 1+i*2);
    }
    if(i < 2){
      llm_triplet = llm_triplet->next;
    }
  }
  

  
  for(int i = 0;i<PLAYER_MAX;i++){
    if(i == 1){
      assert(town_1->chevaliers[i] == 1);
    }
    else {
      assert(town_1->chevaliers[i] == 0);
    }
  }



  llm_field = town_1->lst_champ->head;
  for(int i = 0;i<2;i++){
    test_field = (struct field * )llm_field->data;
    assert(same_card((struct tuille * )test_field->lst_tutuille->head->data,&tutuille_2) == TRUE);
    llm_triplet = test_field->lst_triplet->head;
    for(int j = 0;j<1;j++){
      test_triplet = (struct triplet * )llm_triplet->data;
      assert(test_triplet->x == 11);
      assert(test_triplet->y == 10);
      assert(test_triplet->z == 6+2*i);
    }
    if(i < 1){
      llm_field = llm_field->next;
    }
  }
  
  assert(town_1->len == 2);
  assert(town_1->shield == 2);

  //1 v >1 case//
  MergeTown(town_1,town_3);

  llm_field = town_1->lst_champ->head;
  
  llm_tuille = town_1->lst_tutuille->head;
  test_tuille = (struct tuille * )llm_tuille->data;
  assert(same_card(test_tuille,&tutuille_1) == TRUE); 
  llm_tuille = llm_tuille->next;
  test_tuille = (struct tuille * )llm_tuille->data;
  assert(same_card(test_tuille,&tutuille_2) == TRUE);

  llm_triplet = town_1->lst_triplet->head;
  for(int i = 0;i<4;i++){
    test_triplet = (struct triplet * )llm_triplet->data;
    assert(test_triplet->x == 10);
    assert(test_triplet->y == 10);
    if(i > 1){
      assert(test_triplet->z == 7 - 2*(i-2));
    }
    else{
      assert(test_triplet->z == 1+2*i);
    }
    llm_triplet = llm_triplet->next;
  }
  for(int i = 0;i<3;i++){
    test_triplet = (struct triplet * )llm_triplet->data;
    assert(test_triplet->x == 11);
    assert(test_triplet->y == 10);
    if(i == 2){
      assert(test_triplet->z == 5);
    }
    else {
      assert(test_triplet->z == 1+i*2);
    }
    llm_triplet = llm_triplet->next;
  }
  for(int i = 0;i<1;i++){
    test_triplet = (struct triplet * )llm_triplet->data;
    assert(test_triplet->x == 10);
    assert(test_triplet->y == 9);
    assert(test_triplet->z == 5);
  }
  

  
  for(int i = 0;i<PLAYER_MAX;i++){
    if(i == 1){
      assert(town_1->chevaliers[i] == 1);
    }
    else {
      assert(town_1->chevaliers[i] == 0);
    }
  }



  llm_field = town_1->lst_champ->head;
  for(int i = 0;i<2;i++){
    test_field = (struct field * )llm_field->data;
    assert(same_card((struct tuille * )test_field->lst_tutuille->head->data,&tutuille_2) == TRUE);
    llm_triplet = test_field->lst_triplet->head;
    for(int j = 0;j<1;j++){
      test_triplet = (struct triplet * )llm_triplet->data;
      assert(test_triplet->x == 11);
      assert(test_triplet->y == 10);
      assert(test_triplet->z == 6+2*i);
    }
    llm_field = llm_field->next;
  }
  for(int i = 0;i<1;i++){
    test_field = (struct field * )llm_field->data;
    assert(same_card((struct tuille * )test_field->lst_tutuille->head->data,&tutuille_3) == TRUE);
    llm_triplet = test_field->lst_triplet->head;
    for(int j = 0;j<2;j++){
      test_triplet = (struct triplet * )llm_triplet->data;
      assert(test_triplet->x == 10);
      assert(test_triplet->y == 9);
      assert(test_triplet->z == 8*j);
      if(j < 1){
	llm_triplet = llm_triplet->next;
      }
    }
  }


  assert(town_1->len == 3);
  assert(town_1->shield == 2);

  


  printf("TEST_MERGE_TOWN\t\t\t:");
  printf("\x1b[32m" "\tCHECK\n" "\x1b[0m");
}







void test_Extern_UpdateTown(){
  //init phase//
  struct boardgame test_board;
  initialisation_board(&test_board);

  struct lelement * llm_city;
  struct city * test_city;
  struct lelement * llm_tuille;
  struct tuille * test_tuille;
  struct lelement * llm_field;
  struct field * test_field;
  struct lelement * llm_triplet;
  struct triplet * test_triplet;

  //border = 1//

  //first tuille case//
  UpdateTown(&test_board,test_board.board[72][72]);

  llm_city = test_board.cities->head;
  test_city = (struct city * )llm_city->data;

  llm_tuille = test_city->lst_tutuille->head;
  llm_triplet = test_city->lst_triplet->head;
  llm_field = test_city->lst_champ->head;

  for(int i = 0;i<1;i++){
    test_tuille = (struct tuille * )llm_tuille->data;
    assert(same_card(&test_board.board[72][72],test_tuille) == TRUE);
    if(i < 0){
      llm_tuille = llm_tuille->next;
    }
  }

  for(int i = 0;i<1;i++){
    test_triplet = (struct triplet * )llm_triplet->data;
    assert(test_triplet->x == 72);
    assert(test_triplet->y == 72);
    assert(test_triplet->z == 5);
    if(i < 0){
      llm_triplet = llm_triplet->next;
    }   
  }

  for(int i = 0;i<1;i++){
    test_field = (struct field * )llm_field->data;
    llm_tuille = test_field->lst_tutuille->head;
    test_tuille = (struct tuille * )llm_tuille->data;
    assert(same_card(&test_board.board[72][72],test_tuille) == TRUE);
    llm_triplet = test_field->lst_triplet->head;
    for(int j = 0;j<2;j++){
      test_triplet = (struct triplet * )llm_triplet->data;
      assert(test_triplet->x == 72);
      assert(test_triplet->y == 72);
      assert(test_triplet->z == j*8);
      if(j < 1){
	llm_triplet = llm_triplet->next;
      }
    }
  }

  for(int i = 0;i<PLAYER_MAX;i++){
    assert(test_city->chevaliers[i] == 0);
  }
  
  assert(test_city->border == 1);
  assert(test_city->len == 1);
  assert(test_city->shield == 0);
  
  //adding a corner not full phase//
  struct tuille corner = genere_tuille(23);
  corner.position[0] = 72;
  corner.position[1] = 73;
  corner.dir = 3;
  corner.pion[2][1] = 1;

  test_board.board[72][73] = corner;

  UpdateTown(&test_board,test_board.board[72][73]);

  llm_city = test_board.cities->head;
  test_city = (struct city * )llm_city->data;

  llm_tuille = test_city->lst_tutuille->head;
  llm_triplet = test_city->lst_triplet->head;
  llm_field = test_city->lst_champ->head;

  for(int i = 0;i<2;i++){
    test_tuille = (struct tuille * )llm_tuille->data;
    assert(same_card(&test_board.board[72][72+i],test_tuille) == TRUE);
    if(i < 1){
      llm_tuille = llm_tuille->next;
    }
  }

  for(int i = 0;i<2;i++){
    test_triplet = (struct triplet * )llm_triplet->data;
    assert(test_triplet->x == 72);
    assert(test_triplet->y == 72+i);
    assert(test_triplet->z == 5+2*i);
    if(i < 1){
      llm_triplet = llm_triplet->next;
    }   
  }

  for(int i = 0;i<2;i++){
    test_field = (struct field * )llm_field->data;
    llm_tuille = test_field->lst_tutuille->head;
    test_tuille = (struct tuille * )llm_tuille->data;
    assert(same_card(&test_board.board[72][72+i],test_tuille) == TRUE);
    llm_triplet = test_field->lst_triplet->head;
    if(i == 0){
      for(int j = 0;j<2;j++){
	test_triplet = (struct triplet * )llm_triplet->data;
	assert(test_triplet->x == 72);
	assert(test_triplet->y == 72);
	assert(test_triplet->z == j*8);
	llm_triplet = llm_triplet->next;
      } 
    }
    else{
      for(int j = 0;j<6;j++){
	test_triplet = (struct triplet * )llm_triplet->data;
	assert(test_triplet->x == 72);
	assert(test_triplet->y == 73);
	assert(test_triplet->z == j);
	if(j < 5){
	  llm_triplet = llm_triplet->next;
	}
      } 
    }
    if(i < 1){
      llm_field = llm_field->next;
    }
  }

  for(int i = 0;i<PLAYER_MAX;i++){
    if(i == 1){
      assert(test_city->chevaliers[i] == 1);
    }
    else{
      assert(test_city->chevaliers[i] == 0);
    }
  }
  
  assert(test_city->border == 0);
  assert(test_city->len == 2);
  assert(test_city->shield == 0);


  //border = 2//

  //solo bridge case//
  struct tuille bridge_1 = genere_tuille(18);
  bridge_1.position[0] = 74;
  bridge_1.position[1] = 73;
  


  test_board.board[74][73] = bridge_1;

  UpdateTown(&test_board,test_board.board[74][73]);

  llm_city = test_board.cities->head->next->next;
  test_city = (struct city * )llm_city->data;

  llm_tuille = test_city->lst_tutuille->head;
  llm_triplet = test_city->lst_triplet->head;
  llm_field = test_city->lst_champ->head;

  for(int i = 0;i<1;i++){
    test_tuille = (struct tuille * )llm_tuille->data;
    assert(same_card(&test_board.board[74][73],test_tuille) == TRUE);
    if(i < 0){
      llm_tuille = llm_tuille->next;
    }
  }

  for(int i = 0;i<2;i++){
    test_triplet = (struct triplet * )llm_triplet->data;
    assert(test_triplet->x == 74);
    assert(test_triplet->y == 73);
    assert(test_triplet->z == 1+6*i);
    if(i < 1){
      llm_triplet = llm_triplet->next;
    }   
  }

  for(int i = 0;i<2;i++){
    test_field = (struct field * )llm_field->data;
    llm_tuille = test_field->lst_tutuille->head;
    test_tuille = (struct tuille * )llm_tuille->data;
    assert(same_card(&test_board.board[74][73],test_tuille) == TRUE);
    llm_triplet = test_field->lst_triplet->head;
    for(int j = 0;j<3;j++){
      test_triplet = (struct triplet * )llm_triplet->data;
      assert(test_triplet->x == 74);
      assert(test_triplet->y == 73);
      assert(test_triplet->z == 3+j+6*i);
      llm_triplet = llm_triplet->next;
    } 
    if(i < 1){
      llm_field = llm_field->next;
    }
  }

  for(int i = 0;i<PLAYER_MAX;i++){
      assert(test_city->chevaliers[i] == 0);
  }
  
  assert(test_city->border == 2);
  assert(test_city->len == 1);
  assert(test_city->shield == 0);

  //brdge linking two cities case//
  struct tuille bridge_2 = genere_tuille(18);
  bridge_2.position[0] = 73;
  bridge_2.position[1] = 73;
  


  test_board.board[73][73] = bridge_2;

  UpdateTown(&test_board,test_board.board[73][73]);

  llm_city = test_board.cities->head->next;
  test_city = (struct city * )llm_city->data;

  llm_tuille = test_city->lst_tutuille->head;
  llm_triplet = test_city->lst_triplet->head;
  llm_field = test_city->lst_champ->head;

  for(int i = 0;i<3;i++){
    test_tuille = (struct tuille * )llm_tuille->data;
    if(i == 0){
      assert(same_card(&test_board.board[72][73],test_tuille) == TRUE);
    }
    else if(i < 2){
      assert(same_card(&test_board.board[73][73],test_tuille) == TRUE);
    }
    else{
      assert(same_card(&test_board.board[74][73],test_tuille) == TRUE);
    }
    if(i < 2){
      llm_tuille = llm_tuille->next;
    }
  }

  for(int i = 0;i<5;i++){
    test_triplet = (struct triplet * )llm_triplet->data;
    if(i == 0){
      assert(test_triplet->x == 72);
      assert(test_triplet->z == 5);
    }
    else if(i < 3){
      assert(test_triplet->x ==73);
      assert(test_triplet->z == 1+6*(i-1));
    }
    else{
      assert(test_triplet->x == 74);
      assert(test_triplet->z == 1+6*(i-3));
    }
    assert(test_triplet->y == 73);
    if(i < 4){
      llm_triplet = llm_triplet->next;
    }   
  }

  for(int i = 0;i<5;i++){
    test_field = (struct field * )llm_field->data;
    llm_tuille = test_field->lst_tutuille->head;
    test_tuille = (struct tuille * )llm_tuille->data;
    llm_triplet = test_field->lst_triplet->head;
    if(i == 0){
      assert(same_card(&test_board.board[72][73],test_tuille) == TRUE);
      for(int j = 0;j<6;j++){
	test_triplet = (struct triplet * )llm_triplet->data;
	assert(test_triplet->x == 72);
	assert(test_triplet->y == 73);
	assert(test_triplet->z == j);
	llm_triplet = llm_triplet->next;
      }
    }
    else if(i < 3){
      assert(same_card(&test_board.board[73][73],test_tuille) == TRUE);
      for(int j = 0;j<3;j++){
	test_triplet = (struct triplet * )llm_triplet->data;
	assert(test_triplet->x == 73);
	assert(test_triplet->y == 73);
	assert(test_triplet->z == 3+j+6*(i-1));
	llm_triplet = llm_triplet->next;
      } 
    }
    else{
      assert(same_card(&test_board.board[74][73],test_tuille) == TRUE);
      for(int j = 0;j<3;j++){
	test_triplet = (struct triplet * )llm_triplet->data;
	assert(test_triplet->x == 74);
	assert(test_triplet->y == 73);
	assert(test_triplet->z == 3+j+6*(i-3));
	if(j < 2){
	  llm_triplet = llm_triplet->next;
	}
      } 
    }
    if(i < 4){
      llm_field = llm_field->next;
    }
  }

  for(int i = 0;i<PLAYER_MAX;i++){
    assert(test_city->chevaliers[i] == 0);
  }
  
  assert(test_city->border == 1);
  assert(test_city->len == 3);
  assert(test_city->shield == 0);
  

  //border = 3//

  //solo entry case//
  struct tuille entry_1 = genere_tuille(46);
  entry_1.position[0] = 76;
  entry_1.position[1] = 73;
  entry_1.pion[0][1] = 2;

  test_board.board[76][73] = entry_1;

  UpdateTown(&test_board,test_board.board[76][73]);

  llm_city = test_board.cities->head->next->next;
  test_city = (struct city * )llm_city->data;

  llm_tuille = test_city->lst_tutuille->head;
  llm_triplet = test_city->lst_triplet->head;
  llm_field = test_city->lst_champ->head;

  for(int i = 0;i<1;i++){
    test_tuille = (struct tuille * )llm_tuille->data;
    assert(same_card(&test_board.board[76][73],test_tuille) == TRUE);
    if(i < 0){
      llm_tuille = llm_tuille->next;
    }
  }

  for(int i = 0;i<3;i++){
    test_triplet = (struct triplet * )llm_triplet->data;
    assert(test_triplet->x == 76);
    assert(test_triplet->y == 73);
    assert(test_triplet->z == 1 + i*2);
    if(i < 2){
      llm_triplet = llm_triplet->next;
    }   
  }

  for(int i = 0;i<1;i++){
    test_field = (struct field * )llm_field->data;
    llm_tuille = test_field->lst_tutuille->head;
    test_tuille = (struct tuille * )llm_tuille->data;
    llm_triplet = test_field->lst_triplet->head;
    assert(same_card(&test_board.board[76][73],test_tuille) == TRUE);
    for(int j = 0;j<3;j++){
	test_triplet = (struct triplet * )llm_triplet->data;
	assert(test_triplet->x == 76);
	assert(test_triplet->y == 73);
	assert(test_triplet->z == 6+j);
	if(j < 2){
	  llm_triplet = llm_triplet->next;
	}
    }
    if(i < 0){
      llm_field = llm_field->next;
    }
  }

  for(int i = 0;i<PLAYER_MAX;i++){
    if(i == 2){
      assert(test_city->chevaliers[i] == 1);
    }
    else {
      assert(test_city->chevaliers[i] == 0);
    }
  }
  
  assert(test_city->border == 3);
  assert(test_city->len == 1);
  assert(test_city->shield == 0);

  //adding an entry to a road//
  struct tuille entry_2 = genere_tuille(46);
  entry_2.position[0] = 76;
  entry_2.position[1] = 72;

  test_board.board[76][72] = entry_2;

  UpdateTown(&test_board,test_board.board[76][72]);

  llm_city = test_board.cities->head->next->next;
  test_city = (struct city * )llm_city->data;

  llm_tuille = test_city->lst_tutuille->head;
  llm_triplet = test_city->lst_triplet->head;
  llm_field = test_city->lst_champ->head;

  for(int i = 0;i<2;i++){
    test_tuille = (struct tuille * )llm_tuille->data;
    assert(same_card(&test_board.board[76][73-i],test_tuille) == TRUE);
    if(i < 1){
      llm_tuille = llm_tuille->next;
    }
  }

  for(int i = 0;i<6;i++){
    test_triplet = (struct triplet * )llm_triplet->data;
    if(i < 3){
      assert(test_triplet->x == 76);
      assert(test_triplet->y == 73);
      assert(test_triplet->z == 1 + i*2);
    }
    else{
      assert(test_triplet->x == 76);
      assert(test_triplet->y == 72);
      assert(test_triplet->z == 1 + (i-3)*2);
    }      
    if(i < 5){
      llm_triplet = llm_triplet->next;
    }   
  }

  for(int i = 0;i<2;i++){
    test_field = (struct field * )llm_field->data;
    llm_tuille = test_field->lst_tutuille->head;
    test_tuille = (struct tuille * )llm_tuille->data;
    llm_triplet = test_field->lst_triplet->head;
    assert(same_card(&test_board.board[76][73-i],test_tuille) == TRUE);
    for(int j = 0;j<3;j++){
	test_triplet = (struct triplet * )llm_triplet->data;
	assert(test_triplet->x == 76);
	assert(test_triplet->y == 73-i);
	assert(test_triplet->z == 6+j);
	if(j < 2){
	  llm_triplet = llm_triplet->next;
	}
    }
    if(i < 1){
      llm_field = llm_field->next;
    }
  }

  for(int i = 0;i<PLAYER_MAX;i++){
    if(i == 2){
      assert(test_city->chevaliers[i] == 1);
    }
    else {
      assert(test_city->chevaliers[i] == 0);
    }
  }
  
  assert(test_city->border == 4);
  assert(test_city->len == 2);
  assert(test_city->shield == 0);

  //entry linking two towns case//
  struct tuille single_1 = genere_tuille(15);
  single_1.position[0] = 76;
  single_1.position[1] = 75;
  single_1.dir = 1;

  test_board.board[76][75] = single_1;

  UpdateTown(&test_board,test_board.board[76][75]);

  struct tuille entry_3 = genere_tuille(46);
  entry_3.position[0] = 76;
  entry_3.position[1] = 74;

  test_board.board[76][74] = entry_3;

  UpdateTown(&test_board,test_board.board[76][74]);

  llm_city = test_board.cities->head->next->next;
  test_city = (struct city * )llm_city->data;

  llm_tuille = test_city->lst_tutuille->head;
  llm_triplet = test_city->lst_triplet->head;
  llm_field = test_city->lst_champ->head;

  for(int i = 0;i<4;i++){
    test_tuille = (struct tuille * )llm_tuille->data;
    if(i == 0){
      assert(same_card(&test_board.board[76][73],test_tuille) == TRUE);
    }
    else if(i == 1){
      assert(same_card(&test_board.board[76][72],test_tuille) == TRUE);
    }
    else if(i == 2){
      assert(same_card(&test_board.board[76][74],test_tuille) == TRUE);
    }
    else{
      assert(same_card(&test_board.board[76][75],test_tuille) == TRUE);
    }
    if(i < 3){
      llm_tuille = llm_tuille->next;
    }
  }

  for(int i = 0;i<10;i++){
    test_triplet = (struct triplet * )llm_triplet->data;
    if(i < 3){
      assert(test_triplet->x == 76);
      assert(test_triplet->y == 73);
      assert(test_triplet->z == 1 + i*2);
    }
    else if(i < 6){
      assert(test_triplet->x == 76);
      assert(test_triplet->y == 72);
      assert(test_triplet->z == 1 + (i-3)*2);
    }
    else if(i < 9){
      assert(test_triplet->x == 76);
      assert(test_triplet->y == 74);
      assert(test_triplet->z == 1 + (i-6)*2);
    }
    else{
      assert(test_triplet->x == 76);
      assert(test_triplet->y == 75);
      assert(test_triplet->z == 1);
    }   
    if(i < 9){
      llm_triplet = llm_triplet->next;
    }   
  }

  for(int i = 0;i<4;i++){
    test_field = (struct field * )llm_field->data;
    llm_tuille = test_field->lst_tutuille->head;
    test_tuille = (struct tuille * )llm_tuille->data;
    llm_triplet = test_field->lst_triplet->head;
    if(i == 0){
      assert(same_card(&test_board.board[76][73],test_tuille) == TRUE);
    }
    else if(i == 1){
      assert(same_card(&test_board.board[76][72],test_tuille) == TRUE);
    }
    else if(i == 2){
      assert(same_card(&test_board.board[76][74],test_tuille) == TRUE);
    }
    else{
      assert(same_card(&test_board.board[76][75],test_tuille) == TRUE);
    }
    if(i < 3){
      for(int j = 0;j<3;j++){
	test_triplet = (struct triplet * )llm_triplet->data;
	assert(test_triplet->x == 76);
	if(i == 0){
	  assert(test_triplet->y == 73);
	}
	else if(i == 1){
	  assert(test_triplet->y == 72);
	}
	else{
	  assert(test_triplet->y == 74);
	}
	assert(test_triplet->z == 6+j);
	llm_triplet = llm_triplet->next;
      }
    }
    else{
      for(int j = 0;j<9;j++){
	test_triplet = (struct triplet * )llm_triplet->data;
	assert(test_triplet->x == 76);
	assert(test_triplet->y == 75);
	assert(test_triplet->z == j+3);
	if(j < 8){
	  llm_triplet = llm_triplet->next;
	}
      }
    }
    if(i < 3){
      llm_field = llm_field->next;
    }
  }

  for(int i = 0;i<PLAYER_MAX;i++){
    if(i == 2){
      assert(test_city->chevaliers[i] == 1);
    }
    else {
      assert(test_city->chevaliers[i] == 0);
    }
  }
  
  assert(test_city->border == 4);
  assert(test_city->len == 4);
  assert(test_city->shield == 0);

  //entrance filling a hole//
  struct tuille single_2 = genere_tuille(15);
  struct tuille single_3 = genere_tuille(15);
  struct tuille single_4 = genere_tuille(15);

  single_2.position[0] = 74;
  single_2.position[1] = 69;
  single_2.dir = 3;

  test_board.board[74][69] = single_2;

  UpdateTown(&test_board,test_board.board[74][69]);

  single_3.position[0] = 73;
  single_3.position[1] = 70;
  single_3.dir = 2;

  test_board.board[73][70] = single_3;

  UpdateTown(&test_board,test_board.board[73][70]);

  single_4.position[0] = 74;
  single_4.position[1] = 71;
  single_4.dir = 1;

  test_board.board[74][71] = single_4;

  UpdateTown(&test_board,test_board.board[74][71]);

  struct tuille entry_4 = genere_tuille(43);

  entry_4.position[0] = 74;
  entry_4.position[1] = 70;
  
  test_board.board[74][70] = entry_4;

  UpdateTown(&test_board,test_board.board[74][70]);

  llm_city = test_board.cities->head->next->next->next;
  test_city = (struct city * )llm_city->data;

  llm_tuille = test_city->lst_tutuille->head;
  llm_triplet = test_city->lst_triplet->head;
  llm_field = test_city->lst_champ->head;

  for(int i = 0;i<4;i++){
    test_tuille = (struct tuille * )llm_tuille->data;
    if(i == 0){
      assert(same_card(&test_board.board[73][70],test_tuille) == TRUE);
    }
    else if(i == 1){
      assert(same_card(&test_board.board[74][70],test_tuille) == TRUE);
    }
    else if(i == 2){
      assert(same_card(&test_board.board[74][69],test_tuille) == TRUE);
    }
    else{
      assert(same_card(&test_board.board[74][71],test_tuille) == TRUE);
    }
    if(i < 3){
      llm_tuille = llm_tuille->next;
    }
  }

  for(int i = 0;i<6;i++){
    test_triplet = (struct triplet * )llm_triplet->data;
    if(i == 0){
      assert(test_triplet->x == 73);
      assert(test_triplet->y == 70);
      assert(test_triplet->z == 1);
    }
    else if(i < 4){
      assert(test_triplet->x == 74);
      assert(test_triplet->y == 70);
      assert(test_triplet->z == 1 + (i-1)*2);
    }
    else if(i == 4){
      assert(test_triplet->x == 74);
      assert(test_triplet->y == 69);
      assert(test_triplet->z == 1);
    }
    else{
      assert(test_triplet->x == 74);
      assert(test_triplet->y == 71);
      assert(test_triplet->z == 1);
    }   
    if(i < 5){
      llm_triplet = llm_triplet->next;
    }   
  }

  for(int i = 0;i<4;i++){
    test_field = (struct field * )llm_field->data;
    llm_tuille = test_field->lst_tutuille->head;
    test_tuille = (struct tuille * )llm_tuille->data;
    llm_triplet = test_field->lst_triplet->head;
    if(i == 0){
      assert(same_card(&test_board.board[73][70],test_tuille) == TRUE);
    }
    else if(i == 1){
      assert(same_card(&test_board.board[74][70],test_tuille) == TRUE);
    }
    else if(i == 2){
      assert(same_card(&test_board.board[74][69],test_tuille) == TRUE);
    }
    else{
      assert(same_card(&test_board.board[74][71],test_tuille) == TRUE);
    }
    if(i == 1){
      for(int j = 0;j<3;j++){
	test_triplet = (struct triplet * )llm_triplet->data;
	assert(test_triplet->x == 74);
	assert(test_triplet->y == 70);
	assert(test_triplet->z == 6+j);
	llm_triplet = llm_triplet->next;
      }
    }
    else{
      for(int j = 0;j<9;j++){
	test_triplet = (struct triplet * )llm_triplet->data;
	if(i == 0){
	  assert(test_triplet->x == 73);
	  assert(test_triplet->y == 70);
	}
	else if(i == 2){
	  assert(test_triplet->x == 74);
	  assert(test_triplet->y == 69);
	}
	else{
	  assert(test_triplet->x == 74);
	  assert(test_triplet->y == 71);
	}
	assert(test_triplet->z == j+3);
	if(j < 8 || i < 3){
	  llm_triplet = llm_triplet->next;
	}
      }
    }
    if(i < 3){
      llm_field = llm_field->next;
    }
  }

  for(int i = 0;i<PLAYER_MAX;i++){
    assert(test_city->chevaliers[i] == 0);
  }
  
  assert(test_city->border == 0);
  assert(test_city->len == 4);
  assert(test_city->shield == 1);


  //border = 4//

  //solo center city//
  struct tuille center_1 = genere_tuille(6);
  center_1.position[0] = 76;
  center_1.position[1] = 69;
  
  test_board.board[76][69] = center_1;

  UpdateTown(&test_board,test_board.board[76][69]);

  llm_city = test_board.cities->head->next->next->next->next;
  test_city = (struct city * )llm_city->data;

  llm_tuille = test_city->lst_tutuille->head;
  llm_triplet = test_city->lst_triplet->head;
  llm_field = test_city->lst_champ->head;

  for(int i = 0;i<1;i++){
    test_tuille = (struct tuille * )llm_tuille->data;
    assert(same_card(&test_board.board[76][69],test_tuille) == TRUE);
    if(i < 0){
      llm_tuille = llm_tuille->next;
    }
  }

  for(int i = 0;i<4;i++){
    test_triplet = (struct triplet * )llm_triplet->data;
    assert(test_triplet->x == 76);
    assert(test_triplet->y == 69);
    if(i > 1){
      assert(test_triplet->z == 7-2*(i-2));
    }
    else{
      assert(test_triplet->z == 1+2*i);
    }
    if(i < 3){
      llm_triplet = llm_triplet->next;
    }   
  }

  assert(test_city->lst_champ->head == NULL);

  for(int i = 0;i<PLAYER_MAX;i++){
      assert(test_city->chevaliers[i] == 0);
  }
  
  assert(test_city->border == 4);
  assert(test_city->len == 1);
  assert(test_city->shield == 1);

  //center filling a hole//
  struct tuille single_5 = genere_tuille(15);
  struct tuille single_6 = genere_tuille(15);
  struct tuille single_7 = genere_tuille(15);
  struct tuille single_8 = genere_tuille(15);

  single_5.position[0] = 9;
  single_5.position[1] = 10;
  single_5.dir = 2;

  test_board.board[9][10] = single_5;

  UpdateTown(&test_board,test_board.board[9][10]);

  single_6.position[0] = 10;
  single_6.position[1] = 9;
  single_6.dir = 3;

  test_board.board[10][9] = single_6;

  UpdateTown(&test_board,test_board.board[10][9]);

  single_7.position[0] = 11;
  single_7.position[1] = 10;

  test_board.board[11][10] = single_7;

  UpdateTown(&test_board,test_board.board[11][10]);

  single_8.position[0] = 10;
  single_8.position[1] = 11;
  single_8.dir = 1;

  test_board.board[10][11] = single_8;

  UpdateTown(&test_board,test_board.board[10][11]);

  struct tuille center_2 = genere_tuille(6);
  center_2.position[0] = 10;
  center_2.position[1] = 10;
  
  test_board.board[10][10] = center_2;

  UpdateTown(&test_board,test_board.board[10][10]);

  llm_city = test_board.cities->head->next->next->next->next->next;
  test_city = (struct city * )llm_city->data;

  llm_tuille = test_city->lst_tutuille->head;
  llm_triplet = test_city->lst_triplet->head;
  llm_field = test_city->lst_champ->head;

  for(int i = 0;i<5;i++){
    test_tuille = (struct tuille * )llm_tuille->data;
    if(i == 0){
      assert(same_card(&test_board.board[9][10],test_tuille) == TRUE);
    }
    else if(i == 1){
      assert(same_card(&test_board.board[10][10],test_tuille) == TRUE);
    }
    else if(i == 2){
      assert(same_card(&test_board.board[10][9],test_tuille) == TRUE);
    }
    else if(i == 3){
      assert(same_card(&test_board.board[11][10],test_tuille) == TRUE);
    }
    else{
      assert(same_card(&test_board.board[10][11],test_tuille) == TRUE);
    }
    if(i < 4){
      llm_tuille = llm_tuille->next;
    }
  }

  for(int i = 0;i<8;i++){
    test_triplet = (struct triplet * )llm_triplet->data;
    if(i == 0){
      assert(test_triplet->x == 9);
      assert(test_triplet->y == 10);
      assert(test_triplet->z == 1);
    }
    else if(i < 3){
      assert(test_triplet->x == 10);
      assert(test_triplet->y == 10);
      assert(test_triplet->z == 1 + (i-1)*2);
    }
    else if(i < 5){
      assert(test_triplet->x == 10);
      assert(test_triplet->y == 10);
      assert(test_triplet->z == 7 - (i-3)*2);
    }
    else if(i == 5){
      assert(test_triplet->x == 10);
      assert(test_triplet->y == 9);
      assert(test_triplet->z == 1);
    }
    else if(i == 6){
      assert(test_triplet->x == 11);
      assert(test_triplet->y == 10);
      assert(test_triplet->z == 1);
    }
    else{
      assert(test_triplet->x == 10);
      assert(test_triplet->y == 11);
      assert(test_triplet->z == 1);
    }   
    if(i < 7){
      llm_triplet = llm_triplet->next;
    }   
  }

  for(int i = 0;i<4;i++){
    test_field = (struct field * )llm_field->data;
    llm_tuille = test_field->lst_tutuille->head;
    test_tuille = (struct tuille * )llm_tuille->data;
    llm_triplet = test_field->lst_triplet->head;
    if(i == 0){
      assert(same_card(&test_board.board[9][10],test_tuille) == TRUE);
    }
    else if(i == 1){
      assert(same_card(&test_board.board[10][9],test_tuille) == TRUE);
    }
    else if(i == 2){
      assert(same_card(&test_board.board[11][10],test_tuille) == TRUE);
    }
    else{
      assert(same_card(&test_board.board[10][11],test_tuille) == TRUE);
    }
    for(int j = 0;j<9;j++){
      test_triplet = (struct triplet * )llm_triplet->data;
      if(i == 0){
	assert(test_triplet->x == 9);
	assert(test_triplet->y == 10);
      }
      else if(i == 1){
	assert(test_triplet->x == 10);
	assert(test_triplet->y == 9);
      }
      else if(i == 2){
	assert(test_triplet->x == 11);
	assert(test_triplet->y == 10);
      }
      else{
	assert(test_triplet->x == 10);
	assert(test_triplet->y == 11);
      }   
      assert(test_triplet->z == 3+j);
      if(j < 8){
	llm_triplet = llm_triplet->next;
      }
    }
    if(i < 3){
      llm_field = llm_field->next;
    }
  }

  for(int i = 0;i<PLAYER_MAX;i++){
    assert(test_city->chevaliers[i] == 0);
  }
  
  assert(test_city->border == 0);
  assert(test_city->len == 5);
  assert(test_city->shield == 1);

  
  printf("TEST_EXTERN_UPDATE_TOWN\t\t:");
  printf("\x1b[32m" "\tCHECK\n" "\x1b[0m");
}


//////////////////////////////////////////////

/////////////////MAIN FUNCTION////////////////

int main(){
  test_FieldVide();
  test_TownVide();
  test_ExtractTown();
  test_SingleTripletField();
  test_PluralFieldDouble();
  test_PluralFieldTriple();
  test_InternFusionTown();
  test_MergeTown();
  test_Extern_UpdateTown();
  return 0;
}

//////////////////////////////////////////////
