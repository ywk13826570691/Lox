#include <string.h>
#include "lox_string.h"

int lox_is_int_number(float f)
{
    float f1 = f;
    int f2 = f;
    float f3 = f - f2;
    if (f3 == 0)
    {
        return 1;
    }
    return 0;
}

char *lox_replace_string(char *src, char *target, char *rep_val)
{
    char *p = NULL;
    char *p_last = NULL;
    char *p_res = NULL;
    char *ret = p_res;
    int len = 500;
    int len_cnt = 0;

    if (!src || !target || !rep_val)
    {
        return src;
    }

    if (strlen(target) == 0 || !target)
    {
        return src;
    }

    p = strstr(src, target);

    if (!p)
    {
        return src;
    }
    p_res = (char*)malloc(500);
    ret = p_res;
    len = 500;

    p_last = src;

    if (p_last != p)
    {
        if (len < strlen(rep_val))
        {
            len = len + 500 + strlen(rep_val);
            p_res = realloc(p_res, len + 500 + strlen(rep_val));
        }
        memcpy(p_res, src, p - src);
        len_cnt += (p - src);
        p_res += (p - src);
    }

    p_last = p;
    while(p)
    {
        p = strstr(p + strlen(target), target);
        if (p)
        {
            if (len - len_cnt < strlen(rep_val))
            {
                len = len + 500 + strlen(rep_val);
                p_res = realloc(p_res, len + 500 + strlen(rep_val));
            }

            memcpy(p_res, rep_val, strlen(rep_val));

            len_cnt += strlen(rep_val);
            p_res += strlen(rep_val);

            int len_copy = p - p_last - strlen(target);

            if (len - len_cnt < len_copy)
            {
                len = len + 500 + len_copy;
                p_res = realloc(p_res, len + 500 + len_copy);
            }
            memcpy(p_res, p_last + strlen(target), p - p_last - strlen(target));
            len_cnt += len_copy;
            p_res += len_copy;
            p_last = p;


        }
        else
        {
            if (len - len_cnt < strlen(rep_val))
            {
                len = len + 500 + strlen(rep_val);
                p_res = realloc(p_res, len + 500 + strlen(rep_val));
            }

            memcpy(p_res, rep_val, strlen(rep_val));
            p_res += strlen(rep_val);
            len_cnt += strlen(rep_val);

             int len_copy = src + strlen(src) - p_last - strlen(target);

            if (len - len_cnt < len_copy)
            {
                len = len + 500 + len_copy;
                p_res = realloc(p_res, len + 500 + len_copy);
            }
            memcpy(p_res, p_last + strlen(target), len_copy);
        }
    }
    return ret;
}

char *lox_string_repeat(char *src, int cnt)
{
    int len = (strlen(src) + 1)*cnt;
    char *ret = (char *)malloc(len);
    char *p = ret;
    for(int i = 0; i < cnt; i++)
    {
        memcpy(ret, src, strlen(src));
        ret += strlen(src);
    }
    return p;
}

int lox_string_tolower(char *src)
{
    if (!src)
    {
        return 0;
    }

    int len = strlen(src);
    for (int i =0 ;i < len; i++)
    {
        if(src[i] >= 'a' && src[i] <= 'z')
        {
            src[i] = src[i] - 32;
            continue;
        }
        if(src[i] >= 'A' && src[i] <= 'Z')
        {
            src[i] = src[i] + 32;
            continue;
        }
    }
    return 1;
}
