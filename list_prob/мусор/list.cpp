struct list
{
  int field; // поле данных
  struct list *next; // указатель на следующий элемент
  struct list *prev; // указатель на предыдущий элемент
};

struct list * init(int a)  // а- значение первого узла
{
  struct list *lst;
  // выделение памяти под корень списка
  lst = (struct list*)malloc(sizeof(struct list));
  lst->field = a;
  lst->next = NULL; // указатель на следующий узел
  lst->prev = NULL; // указатель на предыдущий узел
  return(lst);
}

struct list * addelem(list *lst, int number)
{
  struct list *temp, *p;
  temp = (struct list*)malloc(sizeof(list));
  p = lst->next; // сохранение указателя на следующий узел
  lst->next = temp; // предыдущий узел указывает на создаваемый
  temp->field = number; // сохранение поля данных добавляемого узла
  temp->next = p; // созданный узел указывает на следующий узел
  temp->prev = lst; // созданный узел указывает на предыдущий узел
  if (p != NULL)
    p->prev = temp;
  return(temp);
}


struct list * deletelem(list *lst)
{
  struct list *prev, *next;
  prev = lst->prev; // узел, предшествующий lst
  next = lst->next; // узел, следующий за lst
  if (prev != NULL)
    prev->next = lst->next; // переставляем указатель
  if (next != NULL)
    next->prev = lst->prev; // переставляем указатель
  free(lst); // освобождаем память удаляемого элемента
  return(prev);
}

struct list * deletehead(list *root)
{
  struct list *temp;
  temp = root->next;
  temp->prev = NULL;
  free(root);   // освобождение памяти текущего корня
  return(temp); // новый корень списка
}

void listprint(list *lst)
{
  struct list *p;
  p = lst;
  do {
    printf("%d ", p->field); // вывод значения элемента p
    p = p->next; // переход к следующему узлу
  } while (p != NULL); // условие окончания обхода
}

void listprintr(list *lst)
{
  struct list *p;
  p = lst;
  while (p->next != NULL)
    p = p->next;  // переход к концу списка
  do {
    printf("%d ", p->field); // вывод значения элемента p
    p = p->prev; // переход к предыдущему узлу
  } while (p != NULL); // условие окончания обхода
}