#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    short int h, m, s;
} t_time;

typedef struct
{
    t_time *key;
    char *value;
} t_timetable_item;

typedef struct
{
    t_timetable_item *table;
    int size, n;
} t_timetable;

t_time *t_time_init(short int h, short int m, short int s)
{
    if (h < 0 || h > 23 || m < 0 || m > 59 || s < 0 || s > 59)
        return (NULL);

    t_time *t = (t_time *)malloc(sizeof(t_time));

    t->h = h;
    t->m = m;
    t->s = s;

    return (t);
}

int t_time_cmp(t_time *ta, t_time *tb)
{
    int total_sa, total_sb;

    total_sa = ta->h * 3600 + ta->m * 60 + ta->s;
    total_sb = tb->h * 3600 + tb->m * 60 + tb->s;

    if (total_sa > total_sb)
        return (1);
    else if (total_sa < total_sb)
        return (-1);
    else
        return (0);
}

void t_time_free(t_time *t)
{
    free(t);
}

int t_time_get_h(t_time *t) { return t->h; }
int t_time_get_m(t_time *t) { return t->m; }
int t_time_get_s(t_time *t) { return t->s; }

t_timetable *t_timetable_init(int size)
{
    t_timetable *newTt = (t_timetable *)malloc(sizeof(t_timetable));
    (*newTt).table = (t_timetable_item *)malloc(sizeof(t_timetable_item) * size); // array of timetable items
    (*newTt).size = size;
    (*newTt).n = 0;
    return newTt;
}

void t_timetable_put(t_timetable *ttable, t_time *key, char *value)
{
    if (ttable->n == ttable->size)
        exit(-1);

    int i = 0, j;

    while (i < (*ttable).n && t_time_cmp(key, (*ttable).table[i].key) > 0)
        i++;

    for (j = (*ttable).n - 1; j >= i; j--)
    {
        (*ttable).table[j + 1].key = (*ttable).table[j].key;
        (*ttable).table[j + 1].value = (*ttable).table[j].value;
    }

    (*ttable).table[i].key = key;
    (*ttable).table[i].value = value;
    (*ttable).n++;
}

char *t_timetable_get(t_timetable *ttable, t_time *key)
{
    for (int i = 0; i < (*ttable).n; i++)
    {
        if (t_time_cmp((*ttable).table[i].key, key) == 0)
            return (*ttable).table[i].value;
    }
    return NULL;
}

void t_timetable_delete(t_timetable *ttable, t_time *key)
{
    for (int i = 0; i < (*ttable).n; i++)
    {
        if (t_time_cmp((*ttable).table[i].key, key) == 0)
        {
            for (int j = i; j < (*ttable).n - 1; j++)
            {
                (*ttable).table[j].key = (*ttable).table[j + 1].key;
                (*ttable).table[j].value = (*ttable).table[j + 1].value;
            }
            (*ttable).n--;
            break;
        }
    }
}

int t_timetable_contains(t_timetable *ttable, t_time *key)
{
    int found = 0;
    for (int i = 0; i < (*ttable).n; i++)
    {
        if (t_time_cmp((*ttable).table[i].key, key) == 0)
        {
            found = 1;
            break;
        }
    }
    return found;
}

int t_timetable_is_empty(t_timetable *ttable)
{
    return ((*ttable).n == 0);
}

int t_timetable_size(t_timetable *ttable)
{
    return (*ttable).size;
}

t_time *t_timetable_min(t_timetable *ttable)
{
    return (*ttable).table[0].key;
}

t_time *t_timetable_max(t_timetable *ttable)
{
    return (*ttable).table[(*ttable).n].key;
}

t_time t_timetable_delete_min(t_timetable *ttable)
{
    t_timetable_delete(ttable, t_timetable_min(ttable));
}

t_time t_timetable_delete_max(t_timetable *ttable)
{
    t_timetable_delete(ttable, t_timetable_max(ttable));
}

t_time *t_timetable_floor(t_timetable *ttable, t_time *key)
{
    t_time *ttime;
    for (int i = 1; i < (*ttable).n; i++)
    {
        ttime = (*ttable).table[i - 1].key;
        if (t_time_cmp((*ttable).table[i].key, key) == 1)
            break;
    }
    return ttime;
}

t_time *t_timetable_ceil(t_timetable *ttable, t_time *key)
{
    t_time *ttime;
    for (int i = (*ttable).n - 2; i >= 0; i++)
    {
        ttime = (*ttable).table[i + 1].key;
        if (t_time_cmp((*ttable).table[i].key, key) == -1)
            break;
    }
    return ttime;
}

int t_timetable_rank(t_timetable *ttable, t_time *key)
{
    int i;
    for (i = 0; i < (*ttable).n; i++)
    {
        if (t_time_cmp((*ttable).table[i].key, key) == 1)
            break;
    }
    return i;
}

t_time *t_timetable_select(t_timetable *ttable, int k)
{
    return (*ttable).table[k].key;
}

int t_timetable_size_range(t_timetable *ttable, t_time *low, t_time *high)
{
    int count = 0;
    for (int i = 1; i < (*ttable).n; i++)
    {
        if (t_time_cmp((*ttable).table[i].key, low) == 1 && t_time_cmp((*ttable).table[i].key, high) == -1)
            count++;
        if (t_time_cmp((*ttable).table[i].key, high) == 1)
            break;
    }
    return count;
}

t_time *t_timetable_keys(t_timetable *ttable, t_time *low, t_time *high)
{
    t_time *ttime;
    for (int i = 1; i < (*ttable).n; i++)
    {
        if (t_time_cmp((*ttable).table[i].key, low) == 1 && t_time_cmp((*ttable).table[i].key, high) == -1)
        {
            ttime = (*ttable).table[i].key;
            break;
        }
    }
    return ttime;
}

void t_timetable_print(t_timetable *ttable)
{
    for (int i = 0; i < (*ttable).n; i++)
    {
        t_timetable_item table_item = (*ttable).table[i];
        printf("%02d:%02d:%02d => %s\n", t_time_get_h(table_item.key), t_time_get_m(table_item.key), t_time_get_s(table_item.key), table_item.value);
    }
}

void t_timetable_free(t_timetable *ttable)
{
    free(ttable->table);
    free(ttable);
}

int main()
{
    t_time *ttime;
    t_timetable *ttable;
    char *str;
    size_t len;

    int h, m, s, size;

    scanf("%d", &size);
    ttable = t_timetable_init(size);

    scanf("%d:%d:%d", &h, &m, &s);
    while (h >= 0)
    {
        getchar();

        ttime = t_time_init(h, m, s);

        // read string
        str = NULL;
        len = getline(&str, &len, stdin);
        str[len - 1] = '\0';

        t_timetable_put(ttable, ttime, str);

        scanf("%d:%d:%d", &h, &m, &s);
    }

    t_timetable_print(ttable);

    scanf("%d:%d:%d", &h, &m, &s);
    while (h >= 0)
    {
        ttime = t_time_init(h, m, s);
        str = t_timetable_get(ttable, ttime);

        if (str)
            printf("%02d:%02d:%02d => %s\n", h, m, s, str);
        else
            printf("%02d:%02d:%02d => nao encontrado\n", h, m, s);

        scanf("%d:%d:%d", &h, &m, &s);
    }

    t_time_free(ttime);
    t_timetable_free(ttable);
}
