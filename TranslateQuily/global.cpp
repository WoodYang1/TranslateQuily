#include "global.h"


QString formatText(const QString &input)
{

    if (input.isEmpty()) {
        return input;
    }

    QString result;
    QChar prev = input[0];
    result.append(prev.toLower());

    for (int i = 1; i < input.length(); ++i) {
        QChar current = input[i];

        // 情况1：当前字符是大写，且前一个字符不是大写（驼峰拆分）
        if (current.isUpper() && !prev.isUpper()) {
            result.append(' ');
            result.append(current.toLower());
        }
        // 情况2：当前字符是下划线
        else if (current == '_') {
            result.append(' ');
            // 如果下划线后面跟的是字母，下一个循环会处理
        }
        // 情况3：当前字符是大写，且前一个字符也是大写（连续大写不拆分）
        else if (current.isUpper() && prev.isUpper()) {
            // 检查后面是否还有小写字母，如果有，当前大写应该和前面的大写拆开
            if (i + 1 < input.length() && input[i + 1].isLower()) {
                // 例如: "HTTPRequest" → "HTTP Request"
                // 当前字符 'R' 是大写，前一个也是大写，但后面是小写，说明是单词边界
                result.append(' ');
                result.append(current.toLower());
            } else {
                result.append(current.toLower());
            }
        }
        // 情况4：普通字母，直接转小写
        else {
            result.append(current.toLower());
        }

        prev = current;
    }

    return result;
}
