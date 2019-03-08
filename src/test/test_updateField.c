#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../structure/carte.h"
#include "../structure/link.h"
#include "../updateFunctions/updateField.h"

////////////Function used to debug////////////
////////////Affichage d'une tuille ///////////

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

////////////////affichage d'un champ /////////////

void aff_field(struct field * tmp_f){
  printf("----champ----\n");
  printf("len : %d\n",tmp_f->len);
  printf("paysans : ");
  for(int i = 0;i<PLAYER_MAX;i++){
    printf(" player %d : %d |",i,tmp_f->paysans[i]);
  }
  printf("\n");
  printf(" lst_tuille : \n");
  aff_lnk_tuile_town(tmp_f->lst_tutuille);
  printf(" lst_triplet ; \n");
  aff_lnk_triplet(tmp_f->lst_triplet);
  printf("---------------\n");
}


//////////////////////////////////////////////

/////////////////TESTS////////////////////////

void test_ExtractField(){
  //init phase//
  struct tuille center = genere_tuille(6);
  struct tuille cloister = genere_tuille(5);
  struct tuille corner_full_town = genere_tuille(39);
  struct tuille crossroad = genere_tuille(70);

  center.position[0] = 10;
  center.position[1] = 10;
  cloister.position[0] = 20;
  cloister.position[1] = 20;
  corner_full_town.position[0] = 30;
  corner_full_town.position[1] = 30;
  crossroad.position[0] = 40;
  crossroad.position[1] = 40;

  struct tuille tvide = gen_tuile_vide();

  struct field * center_field[12];
  struct field * cloister_field[12];
  struct field * corner_full_field[12];
  struct field * crossroad_field[12];

  for(int i =0;i<12;i++){
    center_field[i] = FieldVide();
    cloister_field[i] = FieldVide();
    corner_full_field[i] = FieldVide();
    crossroad_field[i] = FieldVide();
  }

  struct field * test_field;
  struct tuille * test_tuille;
  struct triplet * test_triplet;
  

  //center town case//
  assert(ExtractField(&center,center_field) == 0);
  
  test_field = center_field[0];
  test_tuille = (struct tuille * )test_field->lst_tutuille->head->data;

  for (int i = 0;i<PLAYER_MAX;i++){
    assert(test_field->paysans[i] == 0);
  }
  assert(test_field->len == NONE);
  assert(same_card(&tvide,test_tuille) == TRUE);

  //cloister case//
  assert(ExtractField(&cloister,cloister_field) == 12);

  for (int i = 0;i<12;i++){
    test_field = cloister_field[i];
    test_tuille = (struct tuille * )test_field->lst_tutuille->head->data;
    assert(same_card(test_tuille,&cloister) == TRUE);
    test_triplet = (struct triplet * )test_field->lst_triplet->head->data;
    assert(test_triplet->x == 20);
    assert(test_triplet->y == 20);
    assert(test_triplet->z == i);
  }

  //corner with road case//
  assert(ExtractField(&corner_full_town,corner_full_field) == 4);

  for (int i = 0;i<4;i++){
    test_field = corner_full_field[i];
    test_tuille = (struct tuille * )test_field->lst_tutuille->head->data;
    assert(same_card(test_tuille,&corner_full_town) == TRUE);
    test_triplet = (struct triplet * )test_field->lst_triplet->head->data;
    assert(test_triplet->x == 30);
    assert(test_triplet->y == 30);
    if(i < 2){
      assert(test_triplet->z == 6+i*2);
    }
    else{
      assert(test_triplet->z == 9+(i-2)*2);
    }
  }

  //crossroad case//
  assert(ExtractField(&crossroad,crossroad_field) == 9);

  for (int i = 0;i<9;i++){
    test_field = crossroad_field[i];
    test_tuille = (struct tuille * )test_field->lst_tutuille->head->data;
    assert(same_card(test_tuille,&crossroad) == TRUE);
    test_triplet = (struct triplet * )test_field->lst_triplet->head->data;
    assert(test_triplet->x == 40);
    assert(test_triplet->y == 40);
    if (i < 4){
      assert(test_triplet->z == i);
    }
    else if(i < 6){
      assert(test_triplet->z == i+1);
    }
    else if(i < 8){
      assert(test_triplet->z == i+2);
    }
    else{
      assert(test_triplet->z == i+3);
    }
  }
  

  printf("TEST_EXTRACT_FIELD\t\t\t:");
  printf("\x1b[32m" "\tCHECK\n" "\x1b[0m");
}


void test_MonasteryField(){
  //init phase//
  struct tuille cloister = genere_tuille(5);
  struct tuille cloister_road = genere_tuille(1);

  cloister.position[0] = 10;
  cloister.position[1] = 10;
  cloister_road.position[0] = 20;
  cloister_road.position[1] = 20;
  
  struct field * cloister_field[12];
  struct field * cloister_road_field[12];

  for(int i =0;i<12;i++){
    cloister_field[i] = FieldVide();
    cloister_road_field[i] = FieldVide();
  }

  struct field * test_field;
  struct triplet * test_triplet;
  struct lelement * llm_triplet;

  int num1 = ExtractField(&cloister,cloister_field);
  int num2 = ExtractField(&cloister_road,cloister_road_field);

  struct field * cloister_f_t1[2];
  struct field * cloister_road_f_t1[2];
  
  for(int i = 0;i<2;i++){
    cloister_f_t1[i] = FieldVide();
    cloister_road_f_t1[i] = FieldVide();
  }

  int len1[2] = {num1,0};
  int len2[2] = {num2,0};

  //cloister case//
  MonasteryField(&cloister,cloister_field,cloister_f_t1,len1);
  
  for(int i = 0;i<1;i++){
    test_field = cloister_field[i];
    test_triplet = (struct triplet * )test_field->lst_triplet->head->data;
    llm_triplet = test_field->lst_triplet->head;
    for (int j = 0;j<12;j++){
      test_triplet = (struct triplet * )llm_triplet->data;
      assert(test_triplet->x == 10);
      assert(test_triplet->y == 10);
      assert(test_triplet->z == j);
      if(j < 11){
	llm_triplet = llm_triplet->next;
      }
    }    
  }

  //cloister road case//
  MonasteryField(&cloister_road,cloister_road_field,cloister_road_f_t1,len2);
  
  for(int i = 0;i<1;i++){
    test_field = cloister_road_field[i];
    test_triplet = (struct triplet * )test_field->lst_triplet->head->data;
    llm_triplet = test_field->lst_triplet->head;
    for (int j = 0;j<11;j++){
      test_triplet = (struct triplet * )llm_triplet->data;
      assert(test_triplet->x == 20);
      assert(test_triplet->y == 20);
      if(j < 7){
	assert(test_triplet->z == j);
      }
      else{
	assert(test_triplet->z == j+1);
      }	
      if(j < 10){
	llm_triplet = llm_triplet->next;
      }
    }    
  }
  


  printf("TEST_MONASTRY_FIELD\t\t\t:");  
  printf("\x1b[32m" "\tCHECK\n" "\x1b[0m");
}



void test_InternFusionFieldTown(){
  //init phase//
  struct tuille entry_road = genere_tuille(49);
  struct tuille single = genere_tuille(15);
  struct tuille crosstown = genere_tuille(32);
  struct tuille single_road = genere_tuille(26);

  entry_road.position[0] = 10;
  entry_road.position[1] = 10;
  single.position[0] = 20;
  single.position[1] = 20;
  crosstown.position[0] = 30;
  crosstown.position[1] = 30;
  single_road.position[0] = 40;
  single_road.position[1] = 40;
  
  struct field * entry_field[12];
  struct field * single_field[12];
  struct field * cross_field[12];
  struct field * single_r_field[12];

  for(int i =0;i<12;i++){
    entry_field[i] = FieldVide();
    single_field[i] = FieldVide();
    cross_field[i] = FieldVide();
    single_r_field[i] = FieldVide();
  }

  struct field * test_field;
  struct triplet * test_triplet;
  struct lelement * llm_triplet;

  int num1 = ExtractField(&entry_road,entry_field);
  int num2 = ExtractField(&single,single_field);
  int num3 = ExtractField(&crosstown,cross_field);
  int num4 = ExtractField(&single_road,single_r_field);

  struct field * entry_f_t1[2];
  struct field * single_f_t1[2];
  struct field * cross_f_t1[2];
  struct field * single_r_f_t1[2];
  
  for(int i = 0;i<2;i++){
    entry_f_t1[i] = FieldVide();
    single_f_t1[i] = FieldVide();
    cross_f_t1[i] = FieldVide();
    single_r_f_t1[i] = FieldVide();
  }

  int len1[2] = {num1,0};
  int len2[2] = {num2,0};
  int len3[2] = {num3,0};
  int len4[2] = {num4,0};

  //entry road case//
  InternFusionFieldTown(&entry_road,entry_field,entry_f_t1,len1);

  for (int i = 0;i<2;i++){
    test_field = entry_field[i];
    test_triplet = (struct triplet * )test_field->lst_triplet->head->data;
    llm_triplet = test_field->lst_triplet->head;
    for (int j = 0;j<1;j++){
      test_triplet = (struct triplet * )llm_triplet->data;
      assert(test_triplet->x == 10);
      assert(test_triplet->y == 10);
      assert(test_triplet->z == 6+2*i);
      if(j < 0){
	llm_triplet = llm_triplet->next;
      }
    }    
  }

  for (int i = 0;i<2;i++){
    test_field = entry_f_t1[i];
    test_triplet = (struct triplet * )test_field->lst_triplet->head->data;
    llm_triplet = test_field->lst_triplet->head;
    for (int j = 0;j<1;j++){
      test_triplet = (struct triplet * )llm_triplet->data;
      assert(test_triplet->x == 10);
      assert(test_triplet->y == 10);
      assert(test_triplet->z == 6+2*i);
      if(j < 0){
	llm_triplet = llm_triplet->next;
      }
    }    
  }

  //single case//
  InternFusionFieldTown(&single,single_field,single_f_t1,len2);

  for (int i = 0;i<1;i++){
    test_field = single_field[i];
    test_triplet = (struct triplet * )test_field->lst_triplet->head->data;
    llm_triplet = test_field->lst_triplet->head;
    for (int j = 0;j<9;j++){
      test_triplet = (struct triplet * )llm_triplet->data;
      assert(test_triplet->x == 20);
      assert(test_triplet->y == 20);
      assert(test_triplet->z == 3+j);
      if(j < 8){
	llm_triplet = llm_triplet->next;
      }
    }    
  }

  for (int i = 0;i<1;i++){
    test_field = single_f_t1[i];
    test_triplet = (struct triplet * )test_field->lst_triplet->head->data;
    llm_triplet = test_field->lst_triplet->head;
    for (int j = 0;j<9;j++){
      test_triplet = (struct triplet * )llm_triplet->data;
      assert(test_triplet->x == 20);
      assert(test_triplet->y == 20);
      assert(test_triplet->z == 3+j);
      if(j < 8){
	llm_triplet = llm_triplet->next;
      }
    }    
  }

  //triple road case//
  InternFusionFieldTown(&crosstown,cross_field,cross_f_t1,len3);

  for (int i = 0;i<3;i++){
    test_field = cross_field[i];
    test_triplet = (struct triplet * )test_field->lst_triplet->head->data;
    llm_triplet = test_field->lst_triplet->head;
    if(i == 0){
      for (int j = 0;j<2;j++){
	test_triplet = (struct triplet * )llm_triplet->data;
	assert(test_triplet->x == 30);
	assert(test_triplet->y == 30);
	assert(test_triplet->z == j*8);
	if(j < 1){
	  llm_triplet = llm_triplet->next;
	}
      }
    }  
    else if(i == 1){
      for (int j = 0;j<2;j++){
      	test_triplet = (struct triplet * )llm_triplet->data;
	assert(test_triplet->x == 30);
	assert(test_triplet->y == 30);
	assert(test_triplet->z == 2+j);
	if(j < 1){
	  llm_triplet = llm_triplet->next;
	}
      }
    }
    else{
      for (int j = 0;j<2;j++){
      	test_triplet = (struct triplet * )llm_triplet->data;
	assert(test_triplet->x == 30);
	assert(test_triplet->y == 30);
	assert(test_triplet->z == 5+j);
	if(j < 1){
	  llm_triplet = llm_triplet->next;
	}
      }
    }
  }

  for (int i = 0;i<1;i++){
    test_field = cross_f_t1[i];
    test_triplet = (struct triplet * )test_field->lst_triplet->head->data;
    llm_triplet = test_field->lst_triplet->head;
    for (int j = 0;j<2;j++){
      test_triplet = (struct triplet * )llm_triplet->data;
      assert(test_triplet->x == 30);
      assert(test_triplet->y == 30);
      assert(test_triplet->z == j*8);
      if(j < 1){
	llm_triplet = llm_triplet->next;
      }
    }    
  }

  //single road case//
  InternFusionFieldTown(&single_road,single_r_field,single_r_f_t1,len4);

  for (int i = 0;i<2;i++){
    test_field = single_r_field[i];
    test_triplet = (struct triplet * )test_field->lst_triplet->head->data;
    llm_triplet = test_field->lst_triplet->head;
    if(i == 0){
      for (int j = 0;j<5;j++){
	test_triplet = (struct triplet * )llm_triplet->data;
	assert(test_triplet->x == 40);
	assert(test_triplet->y == 40);
	assert(test_triplet->z == (3+j)*(j != 4) + 11*(j == 4));
	if(j < 4){
	  llm_triplet = llm_triplet->next;
	}
      }
    }  
    else if(i == 1){
      for (int j = 0;j<2;j++){
      	test_triplet = (struct triplet * )llm_triplet->data;
	assert(test_triplet->x == 40);
	assert(test_triplet->y == 40);
	assert(test_triplet->z == 8+j);
	if(j < 1){
	  llm_triplet = llm_triplet->next;
	}
      }
    }
  }

  for (int i = 0;i<1;i++){
    test_field = single_r_f_t1[i];
    test_triplet = (struct triplet * )test_field->lst_triplet->head->data;
    llm_triplet = test_field->lst_triplet->head;
    for (int j = 0;j<5;j++){
      test_triplet = (struct triplet * )llm_triplet->data;
      assert(test_triplet->x == 40);
      assert(test_triplet->y == 40);
      if(j == 4){
	assert(test_triplet->z == 11);
      }
      else{
	assert(test_triplet->z == 3+j);
      }
      if(j < 4){
	llm_triplet = llm_triplet->next;
      }
    }
  }    


  printf("TEST_INTERN_FUSION_FIELD\t\t:");
  printf("\x1b[32m" "\tCHECK\n" "\x1b[0m");
}
  




void test_InternFusionFieldNoTown(){
  //init phase//
  struct tuille segment = genere_tuille(57);
  struct tuille carrouf = genere_tuille(71);

  segment.position[0] = 10;
  segment.position[1] = 10;
  carrouf.position[0] = 20;
  carrouf.position[1] = 20;
  
  struct field * segment_field[12];
  struct field * carrouf_field[12];

  for(int i =0;i<12;i++){
    segment_field[i] = FieldVide();
    carrouf_field[i] = FieldVide();
  }

  struct field * test_field;
  struct triplet * test_triplet;
  struct lelement * llm_triplet;

  struct field * segment_t_field[2];
  struct field * carrouf_t_field[2];

  for(int i =0;i<2;i++){
    segment_t_field[i] = FieldVide();
    carrouf_t_field[i] = FieldVide();
  }

  int num1 = ExtractField(&segment,segment_field);
  int num2 = ExtractField(&carrouf,carrouf_field);

  int len1[2] = {num1,0};
  int len2[2] = {num2,0};

  //segment case//
  InternFusionFieldNoTown(&segment,segment_field,segment_t_field,len1);

  for (int i = 0;i<2;i++){
    test_field = segment_field[i];
    test_triplet = (struct triplet * )test_field->lst_triplet->head->data;
    llm_triplet = test_field->lst_triplet->head;
    if(i == 0){
      for (int j = 0;j<5;j++){
	test_triplet = (struct triplet * )llm_triplet->data;
	assert(test_triplet->x == 10);
	assert(test_triplet->y == 10);
	if(j == 0){
	  assert(test_triplet->z == 0);
	}
	else{
	  assert(test_triplet->z == 7+j);
	}
	if(j < 4){
	  llm_triplet = llm_triplet->next;
	}
      }
    }  
    else {
      for (int j = 0;j<5;j++){
      	test_triplet = (struct triplet * )llm_triplet->data;
	assert(test_triplet->x == 10);
	assert(test_triplet->y == 10);
	assert(test_triplet->z == 2+j);
	if(j < 4){
	  llm_triplet = llm_triplet->next;
	}
      }
    }
  }

  //carrouf case//
  InternFusionFieldNoTown(&carrouf,carrouf_field,carrouf_t_field,len2);

  for (int i = 0;i<4;i++){
    test_field = carrouf_field[i];
    test_triplet = (struct triplet * )test_field->lst_triplet->head->data;
    llm_triplet = test_field->lst_triplet->head;
    if(i == 0){
      for (int j = 0;j<2;j++){
	test_triplet = (struct triplet * )llm_triplet->data;
	assert(test_triplet->x == 20);
	assert(test_triplet->y == 20);
	if(j == 0){
	  assert(test_triplet->z == 0);
	}
	else{
	  assert(test_triplet->z == 11);
	}
	if(j < 1){
	  llm_triplet = llm_triplet->next;
	}
      }
    }  
    else if(i == 1){
      for (int j = 0;j<2;j++){
      	test_triplet = (struct triplet * )llm_triplet->data;
	assert(test_triplet->x == 20);
	assert(test_triplet->y == 20);
	assert(test_triplet->z == 2+j);
	if(j < 1){
	  llm_triplet = llm_triplet->next;
	}
      }
    }
    else if(i == 2){
      for (int j = 0;j<2;j++){
      	test_triplet = (struct triplet * )llm_triplet->data;
	assert(test_triplet->x == 20);
	assert(test_triplet->y == 20);
	assert(test_triplet->z == 5+j);
	if(j < 1){
	  llm_triplet = llm_triplet->next;
	}
      }
    }
    else {
      for (int j = 0;j<2;j++){
      	test_triplet = (struct triplet * )llm_triplet->data;
	assert(test_triplet->x == 20);
	assert(test_triplet->y == 20);
	assert(test_triplet->z == 8+j);
	if(j < 1){
	  llm_triplet = llm_triplet->next;
	}
      }
    }
  }

  printf("TEST_INTERN_FUSION_FIELD_NO_TOWN\t:");
  printf("\x1b[32m" "\tCHECK\n" "\x1b[0m");
}




void test_MergeField(){
  //init phase//
  struct field * field_1 = FieldVide();
  struct field * field_2 = FieldVide();

  field_1->len = 17;
  field_2->len = 25;
  
  struct tuille tutuille_1 = genere_tuille(1);
  struct tuille tutuille_2 = genere_tuille(10);
  struct tuille tutuille_3 = genere_tuille(15);

  struct lelement * llm_tu_1 = llm_empty();
  struct lelement * llm_tu_2 = llm_empty();
  struct lelement * llm_tu_3 = llm_empty();

  llm_tu_1->data = &tutuille_1;
  llm_tu_2->data = &tutuille_2;
  llm_tu_3->data = &tutuille_3;  

  lnk_add2(field_1->lst_tutuille,llm_tu_1);
  lnk_add2(field_2->lst_tutuille,llm_tu_2);
  lnk_add2(field_2->lst_tutuille,llm_tu_3);

  struct triplet * triplet_1 = (struct triplet * )malloc(sizeof(struct triplet));
  struct triplet * triplet_2 = (struct triplet * )malloc(sizeof(struct triplet));
  struct triplet * triplet_3 = (struct triplet * )malloc(sizeof(struct triplet));
  struct triplet * triplet_4 = (struct triplet * )malloc(sizeof(struct triplet));
  struct triplet * triplet_5 = (struct triplet * )malloc(sizeof(struct triplet));
  struct triplet * triplet_6 = (struct triplet * )malloc(sizeof(struct triplet));
  struct triplet * triplet_7 = (struct triplet * )malloc(sizeof(struct triplet));

  triplet_1->x = 10;
  triplet_1->y = 10;
  triplet_1->z = 0;
  triplet_2->x = 20;
  triplet_2->y = 20;
  triplet_2->z = 3;
  triplet_3->x = 30;
  triplet_3->y = 30;
  triplet_3->z = 6;
  triplet_4->x = 40;
  triplet_4->y = 40;
  triplet_4->z = 9;
  triplet_5->x = 50;
  triplet_5->y = 50;
  triplet_5->z = 12;
  triplet_6->x = 60;
  triplet_6->y = 60;
  triplet_6->z = 15;
  triplet_7->x = 70;
  triplet_7->y = 70;
  triplet_7->z = 18;
  

  struct lelement * llm_tr_1 = llm_empty();
  struct lelement * llm_tr_2 = llm_empty();
  struct lelement * llm_tr_3 = llm_empty();
  struct lelement * llm_tr_4 = llm_empty();
  struct lelement * llm_tr_5 = llm_empty();
  struct lelement * llm_tr_6 = llm_empty();
  struct lelement * llm_tr_7 = llm_empty();

  llm_tr_1->data = triplet_1;
  llm_tr_2->data = triplet_2;
  llm_tr_3->data = triplet_3;
  llm_tr_4->data = triplet_4;
  llm_tr_5->data = triplet_5;
  llm_tr_6->data = triplet_6;
  llm_tr_7->data = triplet_7;

  lnk_add2(field_1->lst_triplet,llm_tr_1);
  lnk_add2(field_1->lst_triplet,llm_tr_2);
  lnk_add2(field_1->lst_triplet,llm_tr_3);
  lnk_add2(field_2->lst_triplet,llm_tr_4);
  lnk_add2(field_2->lst_triplet,llm_tr_5);
  lnk_add2(field_2->lst_triplet,llm_tr_6);
  lnk_add2(field_2->lst_triplet,llm_tr_7);

  field_1->lst_tutuille->head = field_1->lst_tutuille->head->next;
  field_1->lst_tutuille->head->previous = NULL;
  field_2->lst_tutuille->head = field_2->lst_tutuille->head->next;
  field_2->lst_tutuille->head->previous = NULL;

  struct lelement * llm_tuille;
  struct tuille * test_tuille;
  struct lelement * llm_triplet;
  struct triplet * test_triplet;

  //tests//
  MergeField(field_1,field_2);

  llm_tuille = field_1->lst_tutuille->head;
  test_tuille = (struct tuille * )llm_tuille->data;
  assert(same_card(test_tuille,&tutuille_1) == TRUE);
  
  llm_tuille = llm_tuille->next;
  test_tuille = (struct tuille * )llm_tuille->data;
  assert(same_card(test_tuille,&tutuille_2) == TRUE);
	 
  llm_tuille = llm_tuille->next;
  test_tuille = (struct tuille * )llm_tuille->data;
  assert(same_card(test_tuille,&tutuille_3) == TRUE);
	 
  llm_triplet = field_1->lst_triplet->head;
  for(int i = 0;i<7;i++){
    test_triplet = (struct triplet * )llm_triplet->data;
    assert(test_triplet->x == (i+1)*10);
    assert(test_triplet->y == (i+1)*10);
    assert(test_triplet->z == i*3);
    if(i < 6){
      llm_triplet = llm_triplet->next;
    }
  }
    
  assert(field_1->len == 42);
  

  printf("TEST_MERGE_FIELD\t\t\t:");
  printf("\x1b[32m" "\tCHECK\n" "\x1b[0m");
}




void test_ExternFusion_UpdateField(){
  //init phase//
  struct boardgame * b = (struct boardgame * )malloc(sizeof(struct boardgame));
  initialisation_board(b);

  UpdateTown(b,b->board[72][72]);

  struct lelement * llm_town;
  struct city * test_town;
  struct lelement * llm_field;
  struct field * test_field;
  struct lelement * llm_triplet;
  struct triplet * test_triplet;
  
  //init tests//
  UpdateField(b,b->board[72][72]);

  llm_town = b->cities->head;
  test_town = (struct city * )llm_town->data;

  llm_field = test_town->lst_champ->head;
  test_field = (struct field * )llm_field->data;
  
  llm_triplet = test_field->lst_triplet->head;

  for(int i = 0;i<2;i++){
    test_triplet = (struct triplet * )llm_triplet->data;
    assert(test_triplet->x == 72);
    assert(test_triplet->y == 72);
    assert(test_triplet->z == i*8);
    if(i < 1){
      llm_triplet = llm_triplet->next;
    }
  }

  for(int i = 0;i<PLAYER_MAX;i++){
    assert(test_field->paysans[i] == 0);
  }

  assert(test_field->len == 1);
  assert(test_field->inTown == 1);

  llm_field = b->fields->head;
  test_field = (struct field * )llm_field->data;
  llm_triplet = test_field->lst_triplet->head;

  for(int i = 0;i<5;i++){
    test_triplet = (struct triplet * )llm_triplet->data;
    assert(test_triplet->x == 72);
    assert(test_triplet->y == 72);
    assert(test_triplet->z == 2+i);
    if(i < 4){
      llm_triplet = llm_triplet->next;
    }
  }

  assert(test_field->len == 1);
  assert(test_field->inTown == 0);

  //adding a town case//
  struct tuille town_road_1 = genere_tuille(29);
  town_road_1.position[0] = 72;
  town_road_1.position[1] = 73;
  town_road_1.dir = 2;
  
  b->board[72][73] = town_road_1;

  UpdateTown(b,b->board[72][73]);

  UpdateField(b,b->board[72][73]);
  
  llm_town = b->cities->head;
  test_town = (struct city * )llm_town->data;

  llm_field = test_town->lst_champ->head->next;
  test_field = (struct field * )llm_field->data;
  
  llm_triplet = test_field->lst_triplet->head;

  for(int i = 0;i<5;i++){
    test_triplet = (struct triplet * )llm_triplet->data;
    assert(test_triplet->x == 72);
    assert(test_triplet->y == 73);
    if(i == 0){
      assert(test_triplet->z == 0);
    }
    else{
      assert(test_triplet->z == i+4);
    }
    if(i < 4){
      llm_triplet = llm_triplet->next;
    }
  }

  for(int i = 0;i<PLAYER_MAX;i++){
    assert(test_field->paysans[i] == 0);
  }

  assert(test_field->len == 1);
  assert(test_field->inTown == 1);

  llm_field = b->fields->head->next;
  test_field = (struct field * )llm_field->data;

  llm_triplet = test_field->lst_triplet->head;

  for(int i = 0;i<2;i++){
    test_triplet = (struct triplet * )llm_triplet->data;
    assert(test_triplet->x == 72);
    assert(test_triplet->y == 73);
    assert(test_triplet->z == 2+i);
    if(i < 1){
      llm_triplet = llm_triplet->next;
    }
  }

  assert(test_field->len == 1);
  assert(test_field->inTown == 0);

  //adding road cloister case//
  struct tuille cloister_road = genere_tuille(1);
  cloister_road.position[0] = 72;
  cloister_road.position[1] = 74;
  cloister_road.dir = 3;

  b->board[72][74] = cloister_road; 

  UpdateTown(b,b->board[72][74]);

  UpdateField(b,b->board[72][74]);
  
  llm_town = b->cities->head;
  test_town = (struct city * )llm_town->data;

  llm_field = test_town->lst_champ->head->next;
  test_field = (struct field * )llm_field->data;
  
  llm_triplet = test_field->lst_triplet->head;

  for(int i = 0;i<5;i++){
    test_triplet = (struct triplet * )llm_triplet->data;
    assert(test_triplet->x == 72);
    assert(test_triplet->y == 73);
    if(i == 0){
      assert(test_triplet->z == 0);
    }
    else{
      assert(test_triplet->z == i+4);
    }
    if(i < 4){
      llm_triplet = llm_triplet->next;
    }
  }

  for(int i = 0;i<PLAYER_MAX;i++){
    assert(test_field->paysans[i] == 0);
  }

  assert(test_field->len == 1);
  assert(test_field->inTown == 1);

  llm_field = b->fields->head->next;
  test_field = (struct field * )llm_field->data;

  llm_triplet = test_field->lst_triplet->head;

  for(int i = 0;i<2;i++){
    test_triplet = (struct triplet * )llm_triplet->data;
    assert(test_triplet->x == 72);
    assert(test_triplet->y == 73);
    assert(test_triplet->z == 2+i);
    if(i < 1){
      llm_triplet = llm_triplet->next;
    }
  }

  assert(test_field->len == 1);
  assert(test_field->inTown == 0);
  

  printf("TEXT_EXTERN_FUSION_UPDATE_FIELD\t:");
  printf("\x1b[32m" "\tCHECK\n" "\x1b[0m");
}


//////////////////////////////////////////////

/////////////////MAIN FUNCTION////////////////

int main(){
  test_ExtractField();
  test_MonasteryField();
  test_InternFusionFieldTown();
  test_InternFusionFieldNoTown();
  test_MergeField();
  //test_ExternFusion_UpdateField();
  return 0;
}

//////////////////////////////////////////////
