
### 1. Homebrew로 Opencv 설치
⚠️  Homebrew가 없다면 설치합니다. (홈브류 쵝오..)
> /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"

▶️ 다음 명령어를 입력하여 설치합니다. 
> brew update

> brew install opencv

> brew upgrade opencv


![](https://images.velog.io/images/chy0428/post/436a4b64-23ef-40d6-a69d-b28afc2db7a6/image.png)


---

### 2. Xcode setting 

xcode에서 프로젝트를 만들어봅시다!
![](https://images.velog.io/images/chy0428/post/c3ac0dc2-b2ab-4344-9118-b160cbea210b/image.png)

차례차례 적어줍니다.. Opencv C++로 쓸거라서 언어는 C++로 설정합니다.
![](https://images.velog.io/images/chy0428/post/d5d4123a-5cee-4b2d-8c6e-0bf64f03ef81/image.png)

`Build Settings` 탭에 들어갑니다.
![](https://images.velog.io/images/chy0428/post/81178cce-976f-4dc4-a1c4-078e6515f7cc/image.png)

`Search Paths`라고 검색창에 입력합니다. 
![](https://images.velog.io/images/chy0428/post/9bf2533b-98fa-4126-ae23-175c423da65e/image.png)

🔥 여기서부터 왕중요!
#### ✅ Header Search Paths 설정

Header Search Paths에 다음과 같이 입력합니다. 
> /usr/local/Cellar/opencv/[설치한 version]/include/[설치한 opencv]

저는 가장 4.3.0_5 version을 설치하였으므로, 아래와 같이 입력해줍니다. 

> /usr/local/Cellar/opencv/4.3.0_5/include/opencv4

❓ 설치버전 확인 방법
 > ls /usr/local/Cellar/opencv


![](https://images.velog.io/images/chy0428/post/30e26b75-4c34-4578-b1d8-1be85b6d360d/image.png)

Debug, Release 모두 똑같이 입력해야 하는데, 귀찮으니까 `Header Search Paths` 부분의 `+` 눌러서 입력하면 한 번에 작성합니다.
![](https://images.velog.io/images/chy0428/post/7a5b62eb-19c5-4f1b-a104-b10c3a1bb57d/image.png)

#### ✅ Library Search Paths
설치한 버전을 확인한 후, 다음과 같이 입력합니다. 
> /usr/local/Cellar/opencv/[설치 버전]/lib

> /usr/local/Cellar/opencv/4.3.0_5/lib

![](https://images.velog.io/images/chy0428/post/85b42db4-0b53-44fa-a51c-7d37cc8aa68a/image.png)

#### ✅ Linker Flags 
먼저, 터미널을 열고 정확한 version 확인을 합니다.
> ls /usr/local/Cellar/opencv

버전 확인 후, 버전을 알맞게 적어 다음과 같이 터미널에 입력합니다.
아래 나온 결과를 전부 클립보드에 복사합니다. 

> Pkg-config --cflags --libs /usr/local/Cellar/opencv/4.3.0_5/lib/pkgconfig/opencv4.pc

![](https://images.velog.io/images/chy0428/post/5d31e38e-1474-4444-8af8-0e18dc1edb78/image.png)

`Build Settings > Linking`으로 돌아와, `Other Linker Flags` 부분에 복사했던 값들을 붙여넣기 해줍니다. (전부 복붙해야 합니다.)



![](https://images.velog.io/images/chy0428/post/3aa10025-31e5-4b2b-b703-4e9f68739ea6/image.png)

#### ✅ Scheme setting
 
opencv에서는 영상을 불러와서 처리해주는 과정이므로, 간단히 상대 경로를 사용하기 위해 scheme setting에서 working directory 설정을 해줍니다.

상단 메뉴바에서 `Product > Scheme > Edit Schme...` 에 들어가줍니다.
![](https://images.velog.io/images/chy0428/post/e7e9f996-c4e6-4a61-a3d3-40640072182a/image.png)

Use custom working directory에 체크를 한 후, 폴더 부분을 눌러 현재 파일이 실행되는 위치를 클릭해줍니다.

![](https://images.velog.io/images/chy0428/post/fcb2034c-948b-4946-a32c-2f4f7b818910/image.png)
![](https://images.velog.io/images/chy0428/post/f052126b-0d54-40ad-ad1f-3cdf489c86c2/image.png)

---

### 3. 실행 
설치가 잘 완료되었는지 test하기 위해 아래와 같은 간단한 코드를 적어서 실행시켜봅니다.
#### 소스코드
```java

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;

int main() {
    Mat img = imread("lena.png");
    
    if (img.empty()) {
        printf("Image read failed");
        exit(-1);
    }
    
    imshow("image", img);
    waitKey(0);
    return 0;
}
```

#### 실행결과
opencv의 예제에 항상 등장하시는 레나님 반가워용

![](https://images.velog.io/images/chy0428/post/5058cc24-b7cb-4064-b1ff-74b1ca1ea374/image.png)

이렇게 정상적으로 설치가 이루어졌음을 확인할 수 있습니다.

