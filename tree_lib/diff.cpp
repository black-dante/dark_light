#include "tree.cpp"

#define D_l diff(tree1, tree1->nodes[node1]->left, tree2)
#define D_r diff(tree1, tree1->nodes[node1]->right, tree2)
#define add_null(symb) add_node(tree2, strdup(#symb), NULL_NODE, NULL_NODE)


size_t copy(tree_t* tree1, size_t node1, tree_t* tree2)
	{
		if(node1 == NULL_NODE) return NULL_NODE;
		
		add_node(tree2, strdup(tree1->nodes[node1]->data), copy(tree1, tree1->nodes[node1]->left, tree2), copy(tree1, tree1->nodes[node1]->right, tree2));
	}

	
size_t diff(tree_t* tree1, size_t node1, tree_t* tree2)
	{
		static int depth = 0;
	
		depth++;
		
		switch(tree1->nodes[node1]->type)
			{
				case digit:
					depth--;
					return add_node(tree2, strdup("0"), NULL_NODE, NULL_NODE);
					
				break;
				
				case var:
					depth--;
					return add_node(tree2, strdup("1"), NULL_NODE, NULL_NODE);
					
				break;
				
				case oper:
				
					switch(tree1->nodes[node1]->data[0])
						{
							case '+':
								depth--;

								return add_node(tree2, strdup("+"), D_l, D_r);
							
							break;
							
							case '-':
								depth--;
								
								return add_node(tree2, strdup("-"), D_l, D_r);
							
							break;
							
							case '*':
							{
								size_t node_pr = add_node(tree2, strdup("+"), add_null(*), add_null(*));
								
								size_t left = tree2->nodes[node_pr]->left;
								size_t right = tree2->nodes[node_pr]->right;
								
								tree2->nodes[left]->left = diff(tree1, tree1->nodes[node1]->left, tree2);
								tree2->nodes[left]->right = copy(tree1, tree1->nodes[node1]->right, tree2);
								
								tree2->nodes[right]->left = copy(tree1, tree1->nodes[node1]->left, tree2);
								tree2->nodes[right]->right = diff(tree1, tree1->nodes[node1]->right, tree2);
								depth--;
								
								return node_pr; 
							}	
							break;
							
							case '/':
							{
								size_t node_ch = add_node(tree2, strdup("/"), NULL, add_null(*));
								
								size_t left = tree2->nodes[node_ch]->left;
								size_t right = tree2->nodes[node_ch]->right;
								
								tree2->nodes[right]->right = copy(tree1, tree1->nodes[node1]->right, tree2);
								tree2->nodes[right]->left =  copy(tree1, tree1->nodes[node1]->right, tree2);;
								
								tree2->nodes[node_ch]->left = add_node(tree2, strdup("-"), add_null(*), add_null(*));
								size_t node_pr = tree2->nodes[node_ch]->left;
								
								left = tree2->nodes[node_pr]->left;
								right = tree2->nodes[node_pr]->right;

								tree2->nodes[left]->left = diff(tree1, tree1->nodes[node1]->left, tree2);
								tree2->nodes[left]->right = copy(tree1, tree1->nodes[node1]->right, tree2);

								tree2->nodes[right]->left = copy(tree1, tree1->nodes[node1]->left, tree2);
								tree2->nodes[right]->right = diff(tree1, tree1->nodes[node1]->right, tree2);
								depth--;
								
								return node_ch; 
							}	
							break;
						}
				
				break;
				
				default:
					depth--;
					
					printf("WTF\n");
					return NULL_NODE; 
				
				break;
			}
			
		
	}
	