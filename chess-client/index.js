import { Chess } from "chess.js";
import { Chessground } from "@lichess-org/chessground";


const game = new Chess();

const board = Chessground(document.getElementById('board'), {
  dropOffBoard: 'trash',
  sparePieces: true,
  movable: {
    showDests: true,
    draggable: true,
    events: {
      after: (from, to) => {
        try {
          game.move({ from, to, promotion: 'q' });
          board.set({
            fen: game.fen()
          });
        } catch (err) {
          board.set({
            fen: game.fen()
          })
          return;
        }
        if (game.turn() === "b") {
          fetch("http://0.0.0.0:8080")
            .then(res => res.text())
            .then(move => {
              game.move(move)
              board.set({
                fen: game.fen()
              });
            })
            .catch(err => console.log(err))
        }
      }
    }
  },
});