import cv2
import serial

# 设置端口变量和值
serialPosrt = "COM3"
# 设置波特率变量和值
baudRate = 9600
# 设置超时时间,单位为s
timeout = 0.5
# 接受串口数据
# ser = serial.Serial(serialPosrt, baudRate, timeout=timeout)

# 加载表情分类器
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
emotion_classifier = cv2.dnn.readNetFromCaffe('deploy.prototxt', 'emotion_net.caffemodel')
emotion_labels = ['Angry', 'Disgust', 'Fear', 'Happy', 'Sad', 'Surprise', 'Neutral']

def detect_emotion(frame):
    # 将图像转换为灰度图像
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # 检测图像中的人脸
    faces = face_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))

    # 如果没有检测到人脸，返回空串
    if len(faces) == 0:
        return ''

    # 找出最大的人脸
    max_face = faces[0]
    max_area = max_face[2] * max_face[3]
    for face in faces:
        area = face[2] * face[3]
        if area > max_area:
            max_face = face
            max_area = area

    # 提取人脸区域
    x, y, w, h = max_face
    roi_gray = gray[y:y + h, x:x + w]
    roi_color = frame[y:y + h, x:x + w]

    # 调整人脸区域大小
    roi_gray = cv2.resize(roi_gray, (48, 48), interpolation=cv2.INTER_AREA)

    # 进行表情分类
    roi_gray = roi_gray.astype('float') / 255.0
    roi_gray = cv2.dnn.blobFromImage(roi_gray, scalefactor=1.0, size=(48, 48), mean=(0, 0, 0), swapRB=True, crop=False)
    emotion_classifier.setInput(roi_gray)
    preds = emotion_classifier.forward()
    emotion_label = emotion_labels[preds[0].argmax()]

    # 判断表情是否符合要求
    if preds[0].max() > 0.8:
        emotion_str = emotion_label
    else:
        emotion_str = 'Neutral'

    # 返回表情字符串
    return emotion_str


    # 发送表情字符串到串口
    ser.write(emotion_str.encode())


# 打开摄像头
cap = cv2.VideoCapture(0)

# 循环读取摄像头帧
while True:
    # 读取摄像头帧
    ret, frame = cap.read()

    # 检查帧是否读取成功
    if ret:
        # 显示帧
        cv2.imshow('frame', frame)

        com = detect_emotion(frame)
        # ser.write(com.encode('utf-8'))
        print(com)

        # 等待按键按下
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    else:
        break

# 释放摄像头和窗口
cap.release()
cv2.destroyAllWindows()

# 关闭串口
ser.close()
