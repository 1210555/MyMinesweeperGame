//図形の色反転するエリア判定のためのシェーダー
// C++側から受け取る変数 (uniform)
uniform float lineA;             // 直線の方程式 Ax + By + C = 0 の A
uniform float lineB;             // 直線の方程式の B
uniform float lineC;             // 直線の方程式の C

void main() {
    // このピクセルが画面上のどの座標にあるかを取得 (gl_FragCoord)
    vec2 screenPos = gl_FragCoord.xy;

    // 直線の方程式を計算
    float result = lineA * screenPos.x + lineB * screenPos.y + lineC;

    // resultが0より大きい場合（黒い領域側）のみピクセルを描画する
    if (result > 0.0) {
        // テクスチャからピクセルの色を取得し、描画する
        gl_FragColor = gl_Color;
    } else {
        // それ以外の場所（青い領域側）のピクセルは完全に破棄する
        discard;
    }
}