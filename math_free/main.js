var numarr = [];

function replaceResult(find, replaceword, string) {
    var lastIndex = string.lastIndexOf(find);

    if (lastIndex == -1) {
        return string;
    }

    var beginString = string.substring(0, lastIndex);
    var endString = string.substring(lastIndex + find.length);

    return beginString + replaceword + endString
}

function QuickSort(i, j, numarr) {
    if (i >= j) return;
    var pivot = numarr[(i + j)/2];
    var left = i, right = j;

    while (left <= right) {
        while (numarr[left] < pivot) left++;
        while (numarr[right] > pivot) right--;

        if (left <= right) {
            [numarr[left], numarr[right]] = [numarr[right], numarr[left]];
            left++; right--;
        }
    }

    QuickSort(i, right);
    QuickSort(left, j);
}

document.onclick(function() {
    var NgramArr = [];
    var arrResult = {};
    var keyword = [];

    var http = new XMLHttpRequest();
    var url = "https://www.googleapis.com/customsearch/v1?key=AIzaSyAlhfDF75Ue442kBfAt6UCK2d1rvOuFYYc&cx=000280223126909715527:9gbexgde17z&q=" // + keyword

    var imgarr = [];
    var txtArr = [];

    var ParticleData_1 = [
        "은", "는", "이", "가",
        "께서", "에서", "의", "을",
        "를", "에", "에게", "께"
    ]

    var ParticleData_2 = [
        "에게서", "에서부터", "보다", "고",
        "라고", "이라고", "와", "과",
        "랑", "이랑", "같이", "처럼"
    ]

    var ParticleData_3 = [
        "하고", "이며", "하며", "에다", 
        "으로부터", "지만", "이라도", "라도",
        "부터", "로부터", "커녕", "한들",
        "하는"
    ]

    var ParticleData_4 = [
        "인들", "엔들", "마는", "뿐",
        "밖에", "대로", "든가", "든지",
        "나마", "야말로", "말로", "하다", 
        "한다", "하기", "함", "것"
    ]

    var Verb_1 = [
        "지다", "하다", "가다", "치다",
        "서다", "듬다", "이다", "우다",
        "두다", "나다", "돌다", "놓다"
    ]

    var Verb_2 = [
        "리다", "매다", "끼다", "안다",
        "당기다", "내다", "러다", "추다",
        "되다", "채다", "히다", "대다"
    ]

    var Verb_3 = [
        "보다", "막다", "틀다", "굴다",
        "파다", "놓다", "키다"
    ]

    var data = document.getElementById("input").value;

    NgramArr = data.split(",").split(" ");

    for(n = 0; n < NgramArr.length - 1; n += 1) {
        NgramArr[n] = NgramArr[n].replace(ParticleData_4[n], "");
        NgramArr[n] = NgramArr[n].replace(ParticleData_3[n], "");
        NgramArr[n] = NgramArr[n].replace(ParticleData_2[n], "");
        NgramArr[n] = replaceResult(ParticleData_1[n], "", NgramArr[n]);

        if(arrResult.hasOwnProperty(NgramArr[n] == true)) {
            arrResult[NgramArr[n]] += 1;
        }
        else {
            arrResult[NgramArr[n]] = 1;
        }
    }

    obj_result = Object.keys(arrResult).map(function(key) {
        return [Number(key), arrResult[key]]
    })

    for(i = 0; i < obj_result.length - 1; i += 1) {
        numarr[i] = obj_result[i][1];
    }

    QuickSort(0, numarr.length, numarr);
    
    for (num = 0; num < numarr.length; num += 1) {
        if (numarr[num] == obj_result[num][1]) {
            obj_result[num] = keyword[num];

            if(keyword.length() <= 3) break;
        }
    }

    for(n = 0; n < keyword.length - 1; n += 1) {
        txtArr[n] = replaceResult(Verb_1[n], "", keyword[n]);
        txtArr[n] = replaceResult(Verb_2[n], "", keyword[n]);
        txtArr[n] = replaceResult(Verb_3[n], "", keyword[n]);

        for(i = 0; i < txtArr.length - 1; i += 1) {
            if(txtArr[n] == keyword[i]) {
                keyword.splice(i, 1);
            }

            else break;
        }
    }

    var PA = (1%txtArr.length), EA = (1%keyword.length), All = keyword.length + txtArr.length

    for (i = 0; i <= All; i++) {
        (PB%PA)*EA;
    }


    for (a = 0; a <= 2; a++) {
        http.open("get", url + keyword[num] + "&searchType=image");
        http.onload = function() {
            var res = JSON.parse(http.responseText);
            imgarr[a] = res.items.image.thumbnailLink;
        }
    }

    http.send();
})
