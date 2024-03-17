#include "../inc/client.h"

t_response_code handle_server_response(const char *response_str)
{
    if (response_str == NULL)
    {
        return R_INVALID_INPUT;
    }

    cJSON *json = cJSON_Parse(response_str);
    int error_code = get_response_code(json);

    cJSON_Delete(json);

    return error_code;
}
