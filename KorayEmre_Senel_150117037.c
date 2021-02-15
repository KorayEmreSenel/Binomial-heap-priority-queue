//KORAY EMRE SENEL 150117037 
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> 
#include <string.h>
#include <math.h>
#define LENGTH 57
#define Infinity (6000000000L)
#define MaxTrees (12)   
#define Capacity (4095)
#define Error( Str )        FatalError( Str )
#define FatalError( Str )   fprintf( stderr, "%s\n", Str ), exit( 1 )
		struct BinNode;
        typedef struct BinNode *BinTree;
		typedef struct node node;
		typedef struct node *nodePtr;
        struct Collection;
        typedef struct Collection *BinQueue;
        BinQueue Initialize( void );
        void Destroy( BinQueue H );
        void nodePri(nodePtr proNode);
        void deleteList(struct node** head_ref);
        BinQueue MakeEmpty( BinQueue H );
        BinQueue Insert(node Item, BinQueue H );
        node DeleteMin( BinQueue H );
        BinQueue Merge( BinQueue H1, BinQueue H2 );
        node FindMin( BinQueue H );
        int IsEmpty( BinQueue H );
        int IsFull( BinQueue H );
        typedef struct BinNode *Position;

		int eMax , eNet ;
		int jMax;
		BinQueue H1,H2;
		
		struct  node {
		char name[LENGTH];
		int tArr;
		int e;
		int eDefault;
		int waitingTime;
		float priority;
		struct node *next;
		};

		
		//MY METHODS
		void nodeFiller(node *newNode,char *name,int e ,int tArr){
			newNode->e = e;
			newNode->eDefault = e;
			strcpy(newNode->name, name);
			newNode->tArr = tArr;
			newNode->waitingTime = 0;
			newNode->priority = 0;
			newNode->next = NULL;
		}
		
		void nodePri(nodePtr proNode){
			if (proNode->e != proNode->eDefault){
				proNode->priority = (proNode->e/exp(-pow((2 * proNode->e)/(float)(3 * eMax), 3)));
				proNode->priority = proNode->priority + (float)(proNode->tArr*pow(10,-6));
			}
			else {
			proNode->priority = (float)proNode->eDefault;
			proNode->priority = proNode->priority + (float)(proNode->tArr*pow(10,-6));
		}
		}
		
		void keepList(node** header,char *name,int e,int tArr){
				node *newNode,*temp;
				newNode = (node*)malloc(sizeof(node));
				nodeFiller(newNode,name,e,tArr);
				if (*header == NULL){
				*header = newNode;
				eMax = newNode->e;
				eNet = newNode->e;
				}
				else {
				temp = *header;
				while(temp->next != NULL){
				temp = temp->next;
				}
				temp->next = newNode;
				eNet += newNode->e;
				if(newNode->e > eMax)
				eMax = newNode->e;
				}
		}
		
		fileRead(node** header){	
		FILE *cfPtr;
		if((cfPtr = fopen("input.txt","r"))== NULL){
			printf("File could not be opened");
		}
		else {
			int e;
			int tArr;
			char name[LENGTH];
			fscanf(cfPtr,"%10s%d%d",name,&e,&tArr);
			keepList(header,name,e,tArr);
			jMax = 1;
			while(!feof(cfPtr)){	
				fscanf(cfPtr,"%s%d%d",name,&e,&tArr);
				keepList(header,name,e,tArr);
				jMax+=1;
			}
			fclose(cfPtr);
		}
		}
		
		void wtCalc(node** header,int i){
			node* temp= *header;
				int wt = 0 ;	
				wt = i - (temp->eDefault + temp->tArr);
				temp->waitingTime = wt;
		}
		
		
		void pro(BinQueue H1, node** header,int q){
		int a = 0;
		node* temp ;
		node* indicator = *header;
		node snitch;
		do{
			temp = indicator;
			while(temp!=NULL){
				if((temp->tArr) <= a){
					indicator = temp->next;	
					nodePri(temp);
					Insert(*temp,H1);
				}
			temp = temp->next;
			}
			if(!IsEmpty(H1)){
				snitch = FindMin(H1);
				temp = *header;
				while(temp != NULL){
					if(!strcmp(temp->name,snitch.name)){
						if(temp->e > q){
						temp->e -= q;
						DeleteMin(H1);
						nodePri(temp);
						Insert(*temp,H1);
						a=a+q;
						break;
						}
						else if (temp->e == q ){
						a = a + q;
						wtCalc(&temp,a);
						nodePri(temp);
						DeleteMin(H1);
						temp->e -= q; 
						break;
						}
						else{
							a = a + temp->e;
							wtCalc(&temp,a);
							DeleteMin(H1); 
							break;
						}
					}
					temp=temp->next;
				}
			}else return;
		}while(a<eNet);
		
		}
				
		int main(){
			int q = 0 ;
			int j = 0 ;
			int bal= 0;
			H1 = Initialize();
			for (q=1;q<11;q++){
			node *header = NULL;
			fileRead(&header);
			pro(H1,&header,q);
			node* temp = header;
			printf("\n ************************ \n");
			printf("   q = %d \n",q);
			printf(" Name 	Waiting Time \n");
			for(j=0;j<jMax;j++){
				printf(" %s 	 %d \n",temp->name,temp->waitingTime);
				bal += temp->waitingTime;
				temp = temp->next;
			}
			float AWT = (float)bal/jMax;
			printf(" AWT = %d / %d = %.3f",bal,jMax,AWT);
			bal = 0 ;
			printf(" \n");
			deleteList(&header);
		}
		
			return 0;
		}
		
		
				
	struct BinNode{
		    node Item;
            
            Position    LeftChild;
            Position    NextSibling;
        };

        struct Collection{
            int CurrentSize;
            BinTree TheTrees[ MaxTrees ];
        };
        
        BinQueue Initialize( void ){
            BinQueue H;
            int i;

            H = malloc( sizeof( struct Collection ) );
            if( H == NULL )
                FatalError( "Out of space!!!" );
            H->CurrentSize = 0;
            for( i = 0; i < MaxTrees; i++ )
                H->TheTrees[ i ] = NULL;
            return H;
        }

        static void DestroyTree( BinTree T ){
            if( T != NULL )
            {
                DestroyTree( T->LeftChild );
                DestroyTree( T->NextSibling );
                free( T );
            }
        }

        void Destroy( BinQueue H ){
            int i;

            for( i = 0; i < MaxTrees; i++ )
                DestroyTree( H->TheTrees[ i ] );
        }

        BinQueue MakeEmpty( BinQueue H ){
            int i;

            Destroy( H );
            for( i = 0; i < MaxTrees; i++ )
                H->TheTrees[ i ] = NULL;
            H->CurrentSize = 0;

            return H;
        }
        
          int IsEmpty( BinQueue H ){
            return H->CurrentSize == 0;
        }

        int IsFull( BinQueue H ){
            return H->CurrentSize == Capacity;
        }
    
        BinQueue Insert( node Item ,BinQueue H ){
            BinTree NewNode;
            BinQueue OneItem;
			int i;

            NewNode = malloc( sizeof( struct BinNode ) );
            if( NewNode == NULL )
                FatalError( "Out of space!!!" );
            NewNode->LeftChild = NewNode->NextSibling = NULL;
			NewNode->Item = Item;

            OneItem = Initialize( );
            OneItem->CurrentSize = 1;
            OneItem->TheTrees[ 0 ] = NewNode;

            return Merge( H, OneItem );
        }

        node FindMin( BinQueue H ) {
            int i;
            node MinItem;

            if( IsEmpty( H ) )
            {
                return MinItem;
            }

            MinItem.priority = Infinity;
			
            for( i = 0; i < MaxTrees; i++ )
            {
            	
                if( H->TheTrees[ i ] &&
                            H->TheTrees[ i ]->Item.priority < MinItem.priority ) {
                    MinItem = H->TheTrees[ i ]->Item;
				}
				
					
            }

            return MinItem;
        }

       node DeleteMin( BinQueue H ){
            int i, j;
            int MinTree;  
            BinQueue DeletedQueue;
            Position DeletedTree, OldRoot;
            node MinItem;

            if( IsEmpty( H ) )
            {
                return MinItem;
            }

            MinItem.priority = Infinity;
            for( i = 0; i < MaxTrees; i++ )
            {
                if( H->TheTrees[ i ] &&
                    H->TheTrees[ i ]->Item.priority < MinItem.priority )
                {
                    MinItem = H->TheTrees[ i ]->Item;
					
                    MinTree = i;
                }
            }

            DeletedTree = H->TheTrees[ MinTree ];
            OldRoot = DeletedTree;
            DeletedTree = DeletedTree->LeftChild;
            free( OldRoot );

            DeletedQueue = Initialize( );
            DeletedQueue->CurrentSize = ( 1 << MinTree ) - 1;
            for( j = MinTree - 1; j >= 0; j-- )
            {
                DeletedQueue->TheTrees[ j ] = DeletedTree;
                DeletedTree = DeletedTree->NextSibling;
                DeletedQueue->TheTrees[ j ]->NextSibling = NULL;
            }

            H->TheTrees[ MinTree ] = NULL;
            H->CurrentSize -= DeletedQueue->CurrentSize + 1;

            Merge( H, DeletedQueue );
            return MinItem;
        }

        BinTree CombineTrees( BinTree T1, BinTree T2 ){
            if( T1->Item.priority> T2->Item.priority )
                return CombineTrees( T2, T1 );
            T2->NextSibling = T1->LeftChild;
            T1->LeftChild = T2;
            return T1;
        }

        BinQueue Merge( BinQueue H1, BinQueue H2 ){
            BinTree T1, T2, Carry = NULL;
            int i, j;

            if( H1->CurrentSize + H2->CurrentSize > Capacity )
                Error( "Merge would exceed capacity" );

            H1->CurrentSize += H2->CurrentSize;
            for( i = 0, j = 1; j <= H1->CurrentSize; i++, j *= 2 )
            {
                T1 = H1->TheTrees[ i ]; T2 = H2->TheTrees[ i ];

                switch( !!T1 + 2 * !!T2 + 4 * !!Carry )
                {
                    case 0: /* No trees */
                    case 1: /* Only H1 */
                        break;
                    case 2: /* Only H2 */
                        H1->TheTrees[ i ] = T2;
                        H2->TheTrees[ i ] = NULL;
                        break;
                    case 4: /* Only Carry */
                        H1->TheTrees[ i ] = Carry;
                        Carry = NULL;
                        break;
                    case 3: /* H1 and H2 */
                        Carry = CombineTrees( T1, T2 );
                        H1->TheTrees[ i ] = H2->TheTrees[ i ] = NULL;
                        break;
                    case 5: /* H1 and Carry */
                        Carry = CombineTrees( T1, Carry );
                        H1->TheTrees[ i ] = NULL;
                        break;
                    case 6: /* H2 and Carry */
                        Carry = CombineTrees( T2, Carry );
                        H2->TheTrees[ i ] = NULL;
                        break;
                    case 7: /* All three */
                        H1->TheTrees[ i ] = Carry;
                        Carry = CombineTrees( T1, T2 );
                        H2->TheTrees[ i ] = NULL;
                        break;
                }
            }
            return H1;
        }
        
		void deleteList(struct node** head_ref){ 
   		struct node* current = *head_ref; 
   		struct node* next; 
  
   		while (current != NULL)  
  		 { 
   		    next = current->next; 
   		    free(current); 
   		    current = next; 
  		 } 
   		*head_ref = NULL; 
		}	
